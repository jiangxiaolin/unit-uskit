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

#include "unified_scheduler.h"
#include "utils.h"

namespace uskit {

UnifiedScheduler::UnifiedScheduler() {
}

UnifiedScheduler::~UnifiedScheduler() {
}

int UnifiedScheduler::init(const std::string& root_dir, const std::string& usid) {
    // Assemble configuration paths. 配置文件
    std::string backend_config_file(root_dir + "/" + usid + "/" + "backend.conf");
    std::string rank_config_file(root_dir + "/" + usid + "/" + "rank.conf");
    std::string flow_config_file(root_dir + "/" + usid + "/" + "flow.conf");

    // Parse backend configuration. 解析backend配置
    BackendEngineConfig backend_config;
    if (ReadProtoFromTextFile(backend_config_file, &backend_config) != 0) {
        LOG(ERROR) << "Failed to parse backend config, usid [" << usid << "]";
        return -1;
    }

    // Initialize backend engine.  初始化后台引擎
    LOG(INFO) << "Initializing backend engine of usid [" << usid << "]";
    if (_backend_engine.init(backend_config) != 0) {
        LOG(ERROR) << "Failed to initialize backend engine, usid [" << usid << "]";
        return -1;
    }

    // Parse rank configuration.  解析rank配置
    RankEngineConfig rank_config;
    if (ReadProtoFromTextFile(rank_config_file, &rank_config) != 0) {
        LOG(ERROR) << "Failed to parse rank config, usid [" << usid << "]";
        return -1;
    }

    // Initialize rank engine.   初始化rank引擎
    LOG(INFO) << "Initializing rank engine of usid [" << usid << "]";
    if (_rank_engine.init(rank_config) != 0) {
        LOG(ERROR) << "Failed to initialize rank engine, usid [" << usid << "]";
        return -1;
    }

    // Parse flow configuration.  解析flow配置
    FlowEngineConfig flow_config;
    if (ReadProtoFromTextFile(flow_config_file, &flow_config) != 0) {
        LOG(ERROR) << "Failed to parse flow config, usid [" << usid << "]";
        return -1;
    }

    // Initialize flow engine.   初始化flow引擎
    LOG(INFO) << "Initializing flow engine of usid [" << usid << "]";
    if (_flow_engine.init(flow_config) != 0) {
        LOG(ERROR) << "Failed to initialize flow engine, usid [" << usid << "]";
        return -1;
    }

    return 0;
}

int UnifiedScheduler::run(USRequest& request, USResponse& response) const {
    // Run the chat flow.   运行chat flow
    if (_flow_engine.run(request, response, &_backend_engine, &
                        ) != 0) {
        US_LOG(ERROR) << "Failed to run flow engine";
        return -1;
    }

    return 0;
}

} // namespace uskit
