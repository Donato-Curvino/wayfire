#include <climits>
#include <wayfire/plugin.hpp>
#include <wayfire/core.hpp>
#include <wayfire/option-wrapper.hpp>
#include <wayfire/signal-definitions.hpp>

class wayfire_environment : public wf::plugin_interface_t
{
    wf::option_wrapper_t<wf::config::compound_list_t<std::string>> env_entries{"environment/environment"};

    void set_env_vars() const
    {
        for (const auto& [name, value] : env_entries.value())
        {
            setenv(name.c_str(), value.c_str(), true);
        }
    }

    wf::signal::connection_t<wf::reload_config_signal> on_reload_config = [this] (wf::reload_config_signal*)
    {
        set_env_vars();
    };

  public:
    void init() override
    {
        set_env_vars();

        // Set new values when reloading the config
        wf::get_core().connect(&on_reload_config);
    }

    void fini() override
    {
        // Remove callback to prevent undefined behavior from dangling reference
        wf::get_core().disconnect(&on_reload_config);
    }

    int get_order_hint() const override
    {
        // Initialize after the IPC plugin and before anything else
        return INT_MIN + 1;
    };
};

DECLARE_WAYFIRE_PLUGIN(wayfire_environment);
