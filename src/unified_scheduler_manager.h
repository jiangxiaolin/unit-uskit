// Copyright (c) 2018 Baidu, Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef USKIT_REUSABLE_UNIFIED_SCHEDULER_MANAGER_H
#define USKIT_REUSABLE_UNIFIED_SCHEDULER_MANAGER_H

#include <string>
#include <unordered_map>

#include "common.h"
#include "error.h"
#include "unified_scheduler.h"
#include "config.pb.h"
#include "us.pb.h"

namespace uskit
{ 

// Class for managing multiple unified schedulers.
class UnifiedSchedulerManager {
public:
    UnifiedSchedulerManager();
    ~UnifiedSchedulerManager();

    // Initialize all unified schedulers from configuration.  初始化所有的统一调度器
    // Returns 0 on success, -1 otherwise.
    int init(const UnifiedSchedulerConfig &config);
    // Process user request.  处理用户请求，成功返回 0 反之返回-1
    // Returns 0 on success, -1 otherwise.
    int run(BRPC_NAMESPACE::Controller* cntl);

private:
    // Parse user request from HTTP POST body(JSON format). 解析用户请求
    // Returns 0 on success, -1 otherwise.
    int parse_request(BRPC_NAMESPACE::Controller* cntl, USRequest& request);
    // Assemble and send response(HTTP+JSON) back to user.  集成并发送回复给用户
    // Returns 0 on success, -1 otherwise.
    int send_response(BRPC_NAMESPACE::Controller* cntl, USResponse* response,
                      ErrorCode error_code = ErrorCode::OK, const std::string& error_msg = "");

    std::unordered_map<std::string, UnifiedScheduler> _us_map;
    std::vector<std::string> _required_params;
    std::unordered_map<std::string, std::string> _params_default;
    std::unordered_map<std::string, std::string> _params_path;
};
} // namespace uskit

#endif // USKIT_REUSABLE_UNIFIED_SCHEDULER_MANAGER_H
