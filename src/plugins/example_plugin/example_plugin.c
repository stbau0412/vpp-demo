/*
 * example_plugin.c - skeleton vpp engine plug-in
 *
 * Copyright (c) <current-year> <your-organization>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vnet/plugin/plugin.h>
#include <example_plugin/example_plugin.h>

#include <vnet/ip/ip_format_fns.h>

#include <vpp/app/version.h>

example_plugin_main_t example_plugin_main;

/* Action function shared between message handler and debug CLI */

static clib_error_t *
example_plugin_configure_command_fn (vlib_main_t * vm,
                                   unformat_input_t * input,
                                   vlib_cli_command_t * cmd)
{
    example_plugin_main_t *epm = &example_plugin_main;

    u8* str;
    u8 ip_addr_set = 0;
    ip4_address_t ip_addr;

    if (!unformat (input, "%s", &str))
        return clib_error_return (0, "Syntax error");

    if (unformat (input, "address %U", unformat_ip4_address, &ip_addr))
        ip_addr_set = 1;

    if (unformat_check_input (input) != UNFORMAT_END_OF_INPUT)
        return clib_error_return (0, "Syntax error");

    epm->str = str;
    epm->ip_addr_set = ip_addr_set;
    epm->ip_addr = ip_addr;

    vlib_cli_output (vm, "Configuration set");
    return 0;
}


static clib_error_t *
example_plugin_enable_disable_command_fn (vlib_main_t * vm,
                                     unformat_input_t * input,
                                     vlib_cli_command_t * cmd)
{
    example_plugin_main_t *epm = &example_plugin_main;

    u32 enable_disable = 1;
    u32 sw_if_index = ~0;

    while (unformat_check_input (input) != UNFORMAT_END_OF_INPUT)
    {
        if (unformat (input, "disable"))
            enable_disable = 0;
        else if (unformat (input, "interface %U", unformat_vnet_sw_interface,
                           epm->vnet_main, &sw_if_index))
            ;
        else
            return clib_error_return (0, "Syntax error");
    }

    if (sw_if_index == ~0)
        return clib_error_return (0, "Syntax error");

    vnet_feature_enable_disable ("ip4-unicast", "example_plugin",
                                 sw_if_index, enable_disable, 0, 0);

    vlib_cli_output (vm, "Feature enabled/disabled");
    return 0;
}

static clib_error_t * example_plugin_init (vlib_main_t * vm)
{
    example_plugin_main_t * emp = &example_plugin_main;
    emp->vlib_main = vm;
    emp->vnet_main = vnet_get_main();

    return 0;
}

VLIB_INIT_FUNCTION (example_plugin_init);

/* *INDENT-OFF* */
VLIB_CLI_COMMAND (example_plugin_configure_command, static) =
    {
      .path = "example_plugin configure",
      .short_help =
      "example_plugin configure <string> [address <address>]",
      .function = example_plugin_configure_command_fn,
    };
/* *INDENT-ON* */

/* *INDENT-OFF* */
VLIB_CLI_COMMAND (example_plugin_enable_disable_command, static) =
    {
        .path = "example_plugin enable-disable",
        .short_help =
        "example_plugin enable-disable interface <interface> [disable]",
        .function = example_plugin_enable_disable_command_fn,
    };
/* *INDENT-ON* */

/* *INDENT-OFF* */
VLIB_PLUGIN_REGISTER () =
{
  .version = VPP_BUILD_VER,
  .description = "example_plugin plugin description goes here",
};
/* *INDENT-ON* */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
