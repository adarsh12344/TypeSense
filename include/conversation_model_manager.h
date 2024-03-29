#pragma once

#include <shared_mutex>
#include <mutex>
#include <unordered_map>
#include <json.hpp>
#include <option.h>
#include "store.h"
#include "sole.hpp"

class ConversationModelManager
{
    public:
        ConversationModelManager() = delete;
        ConversationModelManager(const ConversationModelManager&) = delete;
        ConversationModelManager(ConversationModelManager&&) = delete;
        ConversationModelManager& operator=(const ConversationModelManager&) = delete;

        static Option<nlohmann::json> get_model(const std::string& model_id);
        static Option<nlohmann::json> add_model(nlohmann::json model);
        static Option<nlohmann::json> delete_model(const std::string& model_id);
        static Option<nlohmann::json> update_model(const std::string& model_id, nlohmann::json model);
        static Option<nlohmann::json> get_all_models();

        
        static Option<int> init(Store* store);
    private:
        static inline std::unordered_map<std::string, nlohmann::json> models;
        static inline std::shared_mutex models_mutex;

        static constexpr char* MODEL_NEXT_ID = "$CVMN";
        static constexpr char* MODEL_KEY_PREFIX = "$CVMP";

        static inline Store* store;
        static const std::string get_model_key(const std::string& model_id);
};