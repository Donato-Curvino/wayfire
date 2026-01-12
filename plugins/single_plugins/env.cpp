#include <cstring>
#include <iostream>
#include <wayfire/plugin.hpp>
#include <wayfire/core.hpp>
#include <wayfire/option-wrapper.hpp>

class wayfire_env : public wf::plugin_interface_t
{
    wf::option_wrapper_t<wf::config::compound_list_t<std::string>> env_entries{"env/env"};

  public:
    void init() override
    {
        /* Run only once, at startup */
        for (const auto& [name, value] : env_entries.value())
        {
            setenv(name.c_str(), value.c_str(), true);
        }
    }
};

DECLARE_WAYFIRE_PLUGIN(wayfire_env);
