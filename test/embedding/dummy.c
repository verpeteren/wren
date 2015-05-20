#include <stdlib.h>
#include <string.h>

#include "dummy.h"

dummy_t * Dummy_New (const char *name)
{
	dummy_t * dummy;

	dummy = malloc( sizeof( *dummy ) );
	if ( dummy != NULL)
	{
		dummy->name = strdup( name );
		if ( dummy->name == NULL )
		{
			free( dummy); dummy = NULL;
		}
	}

	return dummy;
}

void Dummy_Init (dummy_t * dummy)
{
	dummy->name = NULL;
}

void Dummy_Delete (dummy_t * dummy)
{
	if ( dummy->name != NULL )
	{
		free(dummy->name); dummy->name = NULL;
	}

	free( dummy ); dummy = NULL;
}

int Dummy_SetName (dummy_t * dummy, const char * name)
{
	if ( dummy->name != NULL )
	{
		free(dummy->name); dummy->name = NULL;
	}
	dummy->name = strdup( name );

	return ( dummy->name != NULL );
}

const char * Dummy_GetName (dummy_t * dummy)
{

	return dummy->name;
}

