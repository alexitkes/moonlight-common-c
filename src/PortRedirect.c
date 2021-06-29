#include <stdlib.h>

#include "Limelight.h"

static struct __port_redirect_t {
    int source;
    int dest;

    struct __port_redirect_t * next;
} * redirect_list;

int set_port_redirect(int original, int custom)
{
    for (struct __port_redirect_t * p = redirect_list; p; p = p->next) {
        if (p->source == original) {
            p->dest = custom;

            return 0;
        }
    }

    struct __port_redirect_t * new_redirect = (struct __port_redirect_t *) malloc (sizeof (struct __port_redirect_t));

    if (!new_redirect) {
        return -1;
    }

    new_redirect->source = original;
    new_redirect->dest = custom;
    new_redirect->next = redirect_list;

    redirect_list = new_redirect;

    return 0;
}

int get_port_redirect(int original)
{
    for (struct __port_redirect_t * p = redirect_list; p; p = p->next) {
        if (p->source == original) {
            return p->dest;
        }
    }

    return original;
}
