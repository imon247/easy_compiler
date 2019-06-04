typedef enum { typeInt, typeChar, typeStr, typeId, typeOpr, typeArray1, typeArray2, typeArray3 } nodeEnum;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} intNodeType;

typedef struct{
    char value;
}charNodeType;

typedef struct{
    char *value;
}strNodeType;

typedef struct {
    int index;            // index inside the variable array
    int dataType;
}idNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

typedef struct {
    struct nodeTypeTag *arrayID;
    int x;

} array1NodeType;

typedef struct {
    struct nodeTypeTag *arrayID;
    int x;
    int y;
} array2NodeType;

typedef struct {
    struct nodeTypeTag *arrayID;
    int x;
    int y;
    int z;
} array3NodeType;


typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    /* union must be last entry in nodeType */
    /* because operNodeType may dynamically increase */
    union {
        // conNodeType con;        /* constants */
        intNodeType Int;
        charNodeType Char;
        strNodeType Str;
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
        array1NodeType array1;
        array2NodeType array2;
        array3NodeType array3;
    };
} nodeType;

extern int sym[26];
char buffer[100][50];
int bufferIndex;
int variableSPs[50];
