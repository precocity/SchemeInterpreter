#include <stdlib.h>

#include "eval.h"
#include "procedure-utils.h"
#include "scheme-data-types.h"
#include "scheme-procedure-init.h"

#include "procedure-symbol.h"

/**** Private variables ****/

static scheme_procedure _procedure_symbol;
static int _proc_initd = 0;

/**** Private function declarations ****/

/**
 * Implementation of Scheme procedure "symbol?".
 * Check if given argument is a symbol.
 *
 * Will return NULL if:
 *   - Supplied element is not in the format (<element>).
 *   - Out of memory.
 *
 * @param  element  A Scheme element.
 *
 * @return Scheme boolean #t if argument is a symbol, #f if not,
 *   or NULL if an error occurred.
 */
static scheme_element *_symbol_function(scheme_element *element);

/**** Private function implementations ****/

static scheme_element *_symbol_function(scheme_element *element)
{
    // Get arguments.
    int argCount;
    scheme_element **args = procedure_get_arguments(element, &argCount);

    // Check if argument list is invalid.
    if (argCount == -1) return NULL;
    else if (argCount != 1)
    {
        // Wrong number of arguments.
        if (args != NULL) free(args);
        return NULL;
    }

    scheme_element *arg = *args;
    free(args);

    // Evaluate argument.
    arg = scheme_evaluate(arg);

    // Check arg's type.
    int isSymbol = scheme_element_is_type(arg, SCHEME_SYMBOL_TYPE);
    scheme_element_free(arg);

    if (isSymbol)
        return (scheme_element *)scheme_boolean_get_true();
    else
        return (scheme_element *)scheme_boolean_get_false();
}

/**** Public function implementations ****/

scheme_procedure *scheme_procedure_symbol()
{
    if (!_proc_initd)
    {
        scheme_procedure_init(&_procedure_symbol, PROCEDURE_SYMBOL_NAME, _symbol_function);
        _proc_initd = 1;
    }

    return &_procedure_symbol;
}
