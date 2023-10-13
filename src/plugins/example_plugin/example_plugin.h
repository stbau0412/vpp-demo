
/*
 * example_plugin.h - skeleton vpp engine plug-in header file
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
#ifndef __included_example_plugin_h__
#define __included_example_plugin_h__

#include <vnet/vnet.h>
#include <vnet/ip/ip4_packet.h>

typedef struct {
    /* convenience */
    vlib_main_t * vlib_main;
    vnet_main_t * vnet_main;

    u8* str;
    u8 ip_addr_set;
    ip4_address_t ip_addr;
} example_plugin_main_t;

extern example_plugin_main_t example_plugin_main;

#endif /* __included_example_plugin_h__ */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */

