#ifndef INDEX_H
#define INDEX_H 1

/*** Constants Definitions ***/
#define FLAG_LIMIT 100

/*** Type Definitions ***/
typedef unsigned long INDEX;	/* Index Element     */
typedef int INDEX_LIST;			/* Index List Handle */
typedef unsigned char FLAG;

/*** Methods Declarations ***/
#ifdef __STDC__
#include <stdlib.h>
#include <string.h>

INDEX_LIST make_index_list(INDEX, INDEX);		/* allocates a new index list          */
void free_index_list(INDEX_LIST);				/* frees an existing list              */
INDEX choose_index(INDEX_LIST, INDEX);			/* chooses index at specified position */
void remove_index(INDEX_LIST, INDEX);			/* removes specified index from list   */
INDEX index_size(INDEX_LIST);					/* number of indices remaining         */
INDEX pseudo_size(INDEX_LIST);					/* "modified" index size               */

#else

#ifndef NULL
#define NULL 0
#endif /* NULL */

void * malloc();				/* some standard header should define this */
void * realloc();				/* ditto                                   */
void free();					/* ditto                                   */
void * memset();				/* ditto                                   */
void exit();					/* ditto                                   */

INDEX_LIST make_index_list();	/* allocates a new index list          */
void free_index_list();			/* frees an existing list              */
INDEX choose_index();			/* chooses index at specified position */
void remove_index();			/* removes specified index from list   */
INDEX index_size(); 			/* number of indices remaining         */
INDEX pseudo_size();			/* "modified" index size               */

#endif /* __STDC__ */

#endif /* INDEX_H */
