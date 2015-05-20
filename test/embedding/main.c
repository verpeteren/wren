#include <string.h>
#include <stdio.h>

#include <dummy.h>
#include <wren.h>

typedef size_t (*WrenInstantiateFn) (WrenVM* vm);
extern void* wrenGetArgumentData(WrenVM* vm, int index);
extern void wrenDefineInstantiator(WrenVM* vm, const char* className,
                       WrenInstantiateFn instantiator);

static const char * source = "class Dummy { \
	age = ( value ) { \
		_age = value \
	} \
    show { \
		IO.print(\"age = \" + _age ) \
	} \
	foreign new( name ) \
	foreign setName( name ) \
	foreign getName( ) \
	foreign delete( ) \
} \
\
var d = new Dummy( \"wren\" ) \
d.age( 42 ) \
d.show( ) \
";

static size_t dummyInstantiator (WrenVM *vm)
{
	return sizeof( dummy_t );
}

static void dummyInstanceNew (WrenVM* vm)
{
	dummy_t * dummy;
	const char * name;

	dummy = (dummy_t *) wrenGetArgumentData( vm, 0);
	name = wrenGetArgumentString( vm, 1 );
	Dummy_Init( dummy );
	Dummy_SetName( dummy, name );
}

static void dummyInstanceDelete (WrenVM* vm)
{
	dummy_t * dummy;

	dummy = (dummy_t *) wrenGetArgumentData( vm, 0);
	Dummy_Delete( dummy );
}

static void dummyInstanceSetName (WrenVM* vm)
{
	dummy_t * dummy;
	const char * name;

	dummy = (dummy_t *) wrenGetArgumentData( vm, 0);
	name = wrenGetArgumentString( vm, 1 );
	Dummy_SetName( dummy, name );
}

static void dummyInstanceGetName (WrenVM* vm)
{
	dummy_t * dummy;
	const char * name;

	dummy = (dummy_t *) wrenGetArgumentData( vm, 0);
	name = Dummy_GetName( dummy );

	wrenReturnString( vm, name, strlen( name ) );
}

static WrenForeignMethodFn findForeignMethods( WrenVM* vm, const char* module,
	const char* className, bool isStatic, const char* signature )
{
	printf("mod %s, class %s, sign: %s\n", module, className, signature);
	
	if ( strcmp( className, "Dummy" ) == 0 )
	{
		if (isStatic)
		{	
			if ( strcmp( signature, "new(_)" ) == 0 )
			{
				return dummyInstanceNew;
			} 
		} else {
			if ( strcmp( signature, "delete" ) == 0 )
			{
				return dummyInstanceDelete;
			} else if ( strcmp( signature, "setName(_)" ) == 0 ) {
			
				return dummyInstanceSetName;
			} else if ( strcmp( signature, "getName()" ) == 0 ) {
				return dummyInstanceGetName;
			}
		}
	}
	return NULL;
}

static int loadClasses( WrenVM *vm )
{
	int success = 0 ;

	wrenDefineInstantiator( vm, "Dummy", dummyInstantiator );
	
	success = 1;
	return success;
}

int main(const int argc, const char ** argv)
{
	WrenVM *vm;
	WrenConfiguration wrenConf;
	WrenInterpretResult ok;

	memset( &wrenConf, 0, sizeof( wrenConf ) );
	wrenConf.bindForeignMethodFn = findForeignMethods;
	vm = wrenNewVM( &wrenConf );
	if ( vm != NULL )
	{
		if ( loadClasses( vm ) == 1 )
		{
			ok = wrenInterpret( vm, __FILE__, source );
			if ( ok == WREN_RESULT_SUCCESS )
			{
				fprintf( stdout, "ok" );
			} else {
				fprintf( stderr, "Could not run");
			}	
		} else {
			fprintf( stderr, "Could not embed");
		}
		wrenFreeVM( vm );
	} else {
		fprintf( stderr, "Could not start wren");
	}


	return 0;
}
