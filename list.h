#define VAR_NAME_LEN    5

typedef struct varList
{
    char var_name[VAR_NAME_LEN];
    int count;
    struct varList *next;
    int regName;
} varList_t;

extern varList_t *pHead;

extern void SymTable_createVar(char *varName, int regId);
extern void SymTable_traverseList(void);
extern void SymTable_freeList(void);
extern varList_t * SymTable_getNode(char *varName);
extern int SymTable_getLen(void);
extern varList_t * SymTable_removeNode(char *varName);
extern int SymTable_getRegNum(char *varName);