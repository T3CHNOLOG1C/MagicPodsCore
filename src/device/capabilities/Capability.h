// MagicPodsCore: https://github.com/steam3d/MagicPodsCore
// Copyright: 2020-2026 Aleksandr Maslov <https://magicpods.app> & Andrei Litvintsev <a.a.litvintsev@gmail.com>
// License: GPL-3.0

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Event.h"

namespace MagicPodsCore
{
    class Capability
    {
    protected:
        std::string name{};
        bool isReadOnly = false;
        bool isAvailable = false;
        Event<Capability> _onChanged{};
        virtual nlohmann::json CreateJsonBody();

    public:
        explicit Capability(const std::string &name, bool isReadOnly) : name(name), isReadOnly(isReadOnly) {}
        // Public so the device can clear the values itself when its client is given up on while the adapter still reports the device as connected.
        virtual void Reset();
        Event<Capability> &GetChangedEvent()
        {
            return _onChanged;
        }

        const std::string& GetName() const {
            return name;
        }

        nlohmann::json GetAsJson();
        virtual void SetFromJson(const nlohmann::json &json);
        virtual ~Capability() = default;
    };
}