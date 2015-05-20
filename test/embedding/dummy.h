#ifndef _DUMMY_H
#define _DUMMY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _dummy_t {
	char *	name;
} dummy_t;

dummy_t *			Dummy_New		(const char *name);
void 				Dummy_Init		(dummy_t * dummy);
void 				Dummy_Delete	(dummy_t * dummy);
int 				Dummy_SetName	(dummy_t * dummy, const char * name);
const char *		Dummy_GetName	(dummy_t * dummy);

#ifdef __cplusplus
}
#endif

#endif
