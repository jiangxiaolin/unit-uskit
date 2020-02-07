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

#ifndef USKIT_UNIFIED_SCHEDULER_H
#define USKIT_UNIFIED_SCHEDULER_H

#include "common.h"
#include "backend_engine.h"
#include "rank_engine.h"
#include "flow_engine.h"
#include "config.pb.h"

namespace uskit
{
// A unified schedule represents a bot service of a specific dialogue scenario.
// A unified scheduler is composed of 3 engines: backend engine, rank engine and
// flow engine.
class UnifiedScheduler {
public:
    UnifiedScheduler();
    UnifiedScheduler(UnifiedScheduler&&) = default;
    virtual ~UnifiedScheduler();
    // Initialize unified scheduler from configuration. 初始化单个统一调度器
    // Returns 0 on success, -1 otherwise.
    int init(const std::string& root_dir, const std::string& usid);
    // Process user request and generate response.
    // Returns 0 on success, -1 otherwise.
    int run(USRequest& request, USResponse& response) const;

private://每一个统一调度器中，都包含三个策略 分别代表 召回 排序  流程管理
    BackendEngine _backend_engine;
    RankEngine _rank_engine;
    FlowEngine _flow_engine;
};

} // namespace uskit

#endif // USKIT_UNIFIED_SCHEDULER_H
