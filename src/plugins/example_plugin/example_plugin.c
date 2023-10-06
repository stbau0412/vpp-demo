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
example_plugin_command_fn (vlib_main_t * vm,
                                   unformat_input_t * input,
                                   vlib_cli_command_t * cmd)
{
    u8* str;
    u8 ip_addr_set = 0;
    ip4_address_t ip_addr;
    u8* result;

    if (!unformat (input, "%s", &str))
        return clib_error_return (0, "Syntax error");

    if (unformat (input, "address %U", unformat_ip4_address, &ip_addr))
        ip_addr_set = 1;

    if (unformat_check_input (input) != UNFORMAT_END_OF_INPUT)
        return clib_error_return (0, "Syntax error");

    example_plugin_main.str = str;
    example_plugin_main.ip_addr_set = ip_addr_set;
    example_plugin_main.ip_addr = ip_addr;

    result = format(0, "Hello world! (%s)", str);
    if (ip_addr_set)
        result = format(result, " %U", format_ip4_address, &ip_addr);
    vlib_cli_output (vm, (char*)result);
    return 0;
}

/* *INDENT-OFF* */
VLIB_CLI_COMMAND (example_plugin_enable_disable_command, static) =
{
  .path = "example_plugin cmd",
  .short_help =
  "example_plugin cmd <string> [address <address>]",
  .function = example_plugin_command_fn,
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
