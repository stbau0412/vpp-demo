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

#include <vpp/app/version.h>

example_plugin_main_t example_plugin_main;

/* Action function shared between message handler and debug CLI */

static clib_error_t *
example_plugin_command_fn (vlib_main_t * vm,
                                   unformat_input_t * input,
                                   vlib_cli_command_t * cmd)
{
  if (unformat_check_input (input) != UNFORMAT_END_OF_INPUT)
      return clib_error_return (0, "Syntax error");

  vlib_cli_output (vm, "Hello world!");

  return 0;
}

/* *INDENT-OFF* */
VLIB_CLI_COMMAND (example_plugin_enable_disable_command, static) =
{
  .path = "example_plugin cmd",
  .short_help =
  "example_plugin cmd <string>",
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
