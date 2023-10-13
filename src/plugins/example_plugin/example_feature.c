//
// Created by Stephan on 06.10.2023.
//

#include <vlib/vlib.h>
#include <vnet/vnet.h>
#include <vnet/feature/feature.h>

#include <vnet/ip/ip_format_fns.h>

#include <example_plugin/example_plugin.h>

VLIB_NODE_FN (example_plugin_fn) (vlib_main_t * vm,
                        vlib_node_runtime_t * node,
                        vlib_frame_t * frame)
{
    example_plugin_main_t *epm = &example_plugin_main;
    u32 n_left_from, * from, * to_next, next_index;
    u8* result;
    ip4_header_t *ip40;

    from = vlib_frame_vector_args (frame);
    n_left_from = frame->n_vectors;
    next_index = node->cached_next_index;

    while (n_left_from > 0)
    {
        u32 n_left_to_next;

        vlib_get_next_frame (vm, node, next_index,
                             to_next, n_left_to_next);

        while (n_left_from > 0 && n_left_to_next > 0)
        {
            u32 bi0;
            vlib_buffer_t * b0;
            u32 next0;

            bi0 = to_next[0] = from[0];
            from += 1;
            n_left_from -= 1;
            to_next += 1;
            n_left_to_next -= 1;

            b0 = vlib_get_buffer (vm, bi0);
            vnet_feature_next (&next0, b0);

            ip40 = vlib_buffer_get_current (b0);
            if (epm->ip_addr_set && ip40->dst_address.as_u32 != epm->ip_addr.as_u32)
                goto skip;

            result = format(0, "Hello world! (%s)", epm->str);
            if (epm->ip_addr_set)
                result = format(result, " %U", format_ip4_address, &epm->ip_addr);
            vlib_cli_output (vm, (char*)result);

        skip:
            vlib_validate_buffer_enqueue_x1 (vm, node, next_index,
                                             to_next, n_left_to_next,
                                             bi0, next0);
        }

        vlib_put_next_frame (vm, node, next_index, n_left_to_next);
    }
    return frame->n_vectors;
}

/* *INDENT-OFF* */
VLIB_REGISTER_NODE (example_plugin_fn) =
    {
        .name = "example_plugin",
        .vector_size = sizeof (u32),
        .n_errors = 0,
        .n_next_nodes = 0,
    };
/* *INDENT-ON* */

/* *INDENT-OFF* */
VNET_FEATURE_INIT (example_plugin, static) =
    {
        .arc_name = "ip4-unicast",
        .node_name = "example_plugin",
        .runs_before = VNET_FEATURES ("ip4-lookup"),
    };
/* *INDENT-ON* */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
