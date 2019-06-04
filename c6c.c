/*
  this c file is used for generating machine code
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;
static int currentFP = 0;
static int FPoffset = 0;
static int currentSP = 0;
static int previousFP = 0;
static int numOfPara = 0;
static int variableFPs[50];
static int variableTypes[50];
static bool insideProc = false;
int dataType;
int numOfElem;
int numOfArr = 0;
int x, y, z;
void clearFrame();
// int bufferIndex = 0;

typedef struct {
  int aind;
  int x;
  int y;
  int z;
} arrayDimension;

arrayDimension arrayDimensions[100];

int ex(nodeType *p) {
    int lblx, lbly, lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
    case typeChar:
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\t'%c'\n", p->Char.value);
          FPoffset++;
          bufferIndex++;
        }
        else{
          printf("\tpush\t'%c'\n", p->Char.value);
          currentSP++;
        }
        dataType = CHAR;
        break;
    case typeInt:
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\t%d\n", p->Int.value);
          FPoffset++;
          bufferIndex++;
        }
        else{
          printf("\tpush\t%d\n", p->Int.value);
          currentSP++;
        }
        dataType = INTEGER;
        // currentSP++;
        break;
    case typeId:
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->id.index]);
          FPoffset++;
          bufferIndex++;
        }
        else{
          bool found = false;
          for(int i=0;i<numOfArr;i++){
            if(arrayDimensions[i].aind == p->id.index){
              printf("\tpush\t%d\n", variableSPs[p->id.index]);
              found = true;
              break;
            }
          }
          if(found==false){
            printf("\tpush\tsb[%d]\n", variableSPs[p->id.index]);
          }
          currentSP++;
        }
        // currentSP++;
        dataType = variableTypes[p->id.index];
        break;
    case typeStr:
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\t\"%s\"\n", p->Str.value);
          FPoffset++;
          bufferIndex++;
        }
        else{
          printf("\tpush\t\"%s\"\n", p->Str.value);
          currentSP++;
        }
        dataType = STRING;
        break;
    case typeArray1:
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\tsp\n");
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tpush\t%d\n", p->array1.x);
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tadd\n\tpop\tsp\n");
          bufferIndex++;

          variableFPs[p->array1.arrayID->id.index] = FPoffset;
          FPoffset += p->array1.x;
        }
        else{
          printf("\tpush\tsp\n");
          printf("\tpush\t%d\n", p->array1.x);
          printf("\tadd\n\tpop\tsp\n");

          variableSPs[p->array1.arrayID->id.index] = currentSP;
          // printf("SP of the variable: %d\n", variableSPs[p->array1.arrayID->id.index]);
        }

        arrayDimension *ad1;
        ad1 = malloc(sizeof(arrayDimension));
        ad1->aind =p->array1.arrayID->id.index;
        ad1->x = p->array1.x;
        ad1->y = 0;
        ad1->z = 0;
        arrayDimensions[numOfArr] = *ad1;
        numOfArr++;

        currentSP += p->array1.x;
        break;
    case typeArray2:
        numOfElem = p->array2.x * p->array2.y;
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\tsp\n");
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tpush\t%d\n", numOfElem);
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tadd\n\tpop\tsp\n");
          bufferIndex++;

          variableFPs[p->array2.arrayID->id.index] = FPoffset;
          FPoffset += numOfElem;
        }
        else{
          printf("\tpush\tsp\n");
          printf("\tpush\t%d\n", numOfElem);
          printf("\tadd\n\tpop\tsp\n");

          variableSPs[p->array2.arrayID->id.index] = currentSP;
        }

        arrayDimension *ad2;
        ad2 = malloc(sizeof(arrayDimension));
        ad2->aind = p->array2.arrayID->id.index;
        ad2->x = p->array2.x;
        ad2->y = p->array2.y;
        ad2->z = 0;
        arrayDimensions[numOfArr] = *ad2;
        numOfArr++;

        currentSP += numOfElem;
        break;
    case typeArray3:
        numOfElem = (p->array3.x) * (p->array3.y) * (p->array3.z);
        if(insideProc){
          sprintf(buffer[bufferIndex], "\tpush\tsp\n");
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tpush\t%d\n", numOfElem);
          bufferIndex++;
          sprintf(buffer[bufferIndex], "\tadd\n\tpop\tsp\n");
          bufferIndex++;

          variableFPs[p->array3.arrayID->id.index] = FPoffset;
          FPoffset += numOfElem;
        }
        else{
          printf("\tpush\tsp\n");
          printf("\tpush\t%d\n", numOfElem);
          printf("\tadd\n\tpop\tsp\n");

          variableSPs[p->array3.arrayID->id.index] = currentSP;
        }

        arrayDimension *ad3;
        ad3 = malloc(sizeof(arrayDimension));
        ad3->aind = p->array3.arrayID->id.index;
        ad3->x = p->array3.x;
        ad3->y = p->array3.y;
        ad3->z = p->array3.z;
        arrayDimensions[numOfArr] = *ad3;
        numOfArr++;

        currentSP += numOfElem;
        break;
    case typeOpr:
        switch(p->opr.oper) {
      	case FOR:
      		ex(p->opr.op[0]);
          if(insideProc){
            sprintf(buffer[bufferIndex], "L%03d:\n", lblx = lbl++);
            bufferIndex++;
          }
          else
      		  printf("L%03d:\n", lblx = lbl++);
      		ex(p->opr.op[1]);
          if(insideProc){
            sprintf(buffer[bufferIndex], "\tj0\tL%03d\n", lbly = lbl++);
            bufferIndex++;
          }
          else
      		  printf("\tj0\tL%03d\n", lbly = lbl++);
      		ex(p->opr.op[3]);
      		ex(p->opr.op[2]);
          if(insideProc){
            sprintf(buffer[bufferIndex], "\tjmp\tL%03d\n", lblx);
            bufferIndex++;
        		sprintf(buffer[bufferIndex], "L%03d:\n", lbly);
            bufferIndex++;
          }
          else{
      		  printf("\tjmp\tL%03d\n", lblx);
      		  printf("L%03d:\n", lbly);
          }
      		break;
        case WHILE:
            if(insideProc){
              printf(buffer[bufferIndex], "L%03d:\n", lbl1 = lbl++);
              bufferIndex++;
            }
            else
              printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tj0\tL%03d\n", lbl2 = lbl++);
              bufferIndex++;
            }
            else
              printf("\tj0\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tjmp\tL%03d\n", lbl1);
              bufferIndex++;
              sprintf(buffer[bufferIndex], "L%03d:\n", lbl2);
              bufferIndex++;
            }
            else{
              printf("\tjmp\tL%03d\n", lbl1);
              printf("L%03d:\n", lbl2);
            }
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                if(insideProc){
                  sprintf(buffer[bufferIndex], "\tj0\tL%03d\n", lbl1 = lbl++);
                  bufferIndex++;
                }
                else
                  printf("\tj0\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                if(insideProc){
                  sprintf(buffer[bufferIndex], "\tjmp\tL%03d\n", lbl2 = lbl++);
                  bufferIndex++;
                  sprintf(buffer[bufferIndex], "L%03d:\n", lbl1);
                  bufferIndex++;
                }
                else{
                  printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                  printf("L%03d:\n", lbl1);
                }
                ex(p->opr.op[2]);
                if(insideProc){
                  sprintf(buffer[bufferIndex], "L%03d:\n", lbl2);
                  bufferIndex++;
                }
                else
                  printf("L%03d:\n", lbl2);
            } else {
                /* if */
                if(insideProc){
                  sprintf(buffer[bufferIndex], "\tj0\tL%03d\n", lbl1 = lbl++);
                  bufferIndex++;
                }
                else
                  printf("\tj0\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                if(insideProc){
                  sprintf(buffer[bufferIndex], "L%03d:\n", lbl1);
                  bufferIndex++;
                }
                else
                  printf("L%03d:\n", lbl1);
            }
            break;
      	case READ:
            printf("\tpush\tsp\n\tpush\t1\n\tadd\n\tpop\tsp\n");
      	    printf("\tgeti\n");
            currentSP += 1;
            dataType = INTEGER;
            if(variableSPs[p->opr.op[0]->id.index]<0){
              variableSPs[p->opr.op[0]->id.index] = currentSP-1;
            }
            variableTypes[p->opr.op[0]->id.index] = INTEGER;
            printf("\tpop\tsb[%d]\n", variableSPs[p->opr.op[0]->id.index]);
      	    break;
        case PRINT:
            ex(p->opr.op[0]);
            if(dataType==INTEGER){
              printf("\tputi\n");
            }
            else if(dataType==CHAR){
              printf("\tputc\n");
            }
            else if(dataType==STRING){
              printf("\tputs\n");
            }
            else{
              printf("\tputi\n");
            }
            currentSP--;
            break;
        case '=':
            for(int i=0;i<numOfArr;i++){
              if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                printf("syntax error: cannot assign value to array addr!\n");
                exit(1);
              }
            }
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tpush\tsp\n\tpush\t1\n\tadd\n\tpop\tsp\n");
              bufferIndex++;
            }
            else{
              printf("\tpush\tsp\n\tpush\t1\n\tadd\n\tpop\tsp\n");
            }
            ex(p->opr.op[1]);
            if(insideProc){
              if(p->opr.op[1]->type==typeOpr && p->opr.op[1]->opr.oper==PROC){
                variableFPs[p->opr.op[0]->id.index] = FPoffset;
                sprintf(buffer[bufferIndex], "\tpop\tfp[%d]\n", FPoffset);
                bufferIndex++;
              }
              else{
                variableFPs[p->opr.op[0]->id.index] = FPoffset-1;
                sprintf(buffer[bufferIndex], "\tpop\tfp[%d]\n", FPoffset-1);
                bufferIndex++;
              }
            }
            else{
                /* check if declared before */
                if(variableSPs[p->opr.op[0]->id.index] == -1){
                  variableSPs[p->opr.op[0]->id.index] = currentSP-1;
                }
                printf("\tpop\tsb[%d]\n", variableSPs[p->opr.op[0]->id.index]);
            }
            variableTypes[p->opr.op[0]->id.index] = dataType;
            break;
        case ',':
            variableFPs[p->opr.op[1]->id.index] = -4 - numOfPara;
            numOfPara++;
            ex(p->opr.op[0]);
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tneg\n");
              bufferIndex++;
            }
            else
              printf("\tneg\n");
            break;
        case ARG:
            ex(p->opr.op[1]);
            numOfPara++;
            ex(p->opr.op[0]);
            break;
        case DECLARE:
            if(variableSPs[p->opr.op[0]->id.index]<0){
              variableSPs[p->opr.op[0]->id.index] = lbl;
              lbl++;
            }
            insideProc = true;
            sprintf(buffer[bufferIndex], "L%03d:", variableSPs[p->opr.op[0]->id.index]);
            bufferIndex++;
            ex(p->opr.op[1]);   // vars
            numOfPara = 0;
            ex(p->opr.op[2]);
            clearFrame(FPoffset);
            sprintf(buffer[bufferIndex], "\tret\n");
            bufferIndex++;
            insideProc = false;
            FPoffset = 0;
            break;
        case PROC:
            if(variableSPs[p->opr.op[1]->id.index]<0){
              variableSPs[p->opr.op[1]->id.index] = lbl;
              lbl++;
            }
            variableTypes[p->opr.op[1]->id.index] = PROC;
            ex(p->opr.op[0]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tcall\tL%03d, %d\n", variableSPs[p->opr.op[0]->id.index], numOfPara);
              bufferIndex++;
            }
            else{
              printf("\tcall\tL%03d, %d\n", variableSPs[p->opr.op[0]->id.index], numOfPara);
              currentSP -= numOfPara-1;
            }
            numOfPara = 0;
            break;
        case RETURN:
            ex(p->opr.op[0]);
            currentFP = previousFP;
            break;
        case A1ELEM:
            ex(p->opr.op[1]);                 /* first index */
            // ex(p->opr.op[0]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpush\tsb[in]\n");
              bufferIndex++;
            }
            else{
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);
              printf("\tadd\n\tpop\tin\n\tpush\tsb[in]\n");
            }
            break;
        case A2ELEM:
            ex(p->opr.op[1]);                 /* first index */
            if(insideProc){
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n\tmul\n", arrayDimensions[i].y); bufferIndex++;
                  break;
                }
              }
              ex(p->opr.op[2]);               /* second index */
              sprintf(buffer[bufferIndex], "\tadd\n"); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpush\tsb[in]\n"); bufferIndex++;
            }
            else{
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  printf("\tpush\t%d\n\tmul\n", arrayDimensions[i].y);
                  break;
                }
              }
              ex(p->opr.op[2]);
              printf("\tadd\n");
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);      /* address of the start of the array */
              printf("\tadd\n\tpop\tin\n\tpush\tsb[in]\n");
            }
            break;
        case A3ELEM:
            ex(p->opr.op[1]);                     /* first index */
            if(insideProc){
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n\tpush\t%d\n\tmul\n\tmul\n", arrayDimensions[i].y, arrayDimensions[i].z);
                  bufferIndex++;
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n", arrayDimensions[i].z); bufferIndex++;
                  break;
                }
              }
              ex(p->opr.op[2]);         /* second index */
              sprintf(buffer[bufferIndex], "\tmul\n\tadd\n"); bufferIndex++;
              ex(p->opr.op[3]);         /* third index */
              sprintf(buffer[bufferIndex], "\tadd\n"); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpush\tsb[in]\n"); bufferIndex++;
            }
            else{
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  printf("\tpush\t%d\n\tpush\t%d\n\tmul\n\tmul\n", arrayDimensions[i].y, arrayDimensions[i].z);
                  printf("\tpush\t%d\n", arrayDimensions[i].z);
                  break;
                }
              }
              ex(p->opr.op[2]);         /* second index */
              printf("\tmul\n\tadd\n");
              ex(p->opr.op[3]);         /* third index */
              printf("\tadd\n");
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);
              printf("\tadd\n\tpop\tin\n\tpush\tsb[in]\n");
            }
            break;
        case ASSIGN_ARR1:
            ex(p->opr.op[2]);
            ex(p->opr.op[1]);
            if(insideProc){
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]);  // pass in the address of the start of the array
              bufferIndex++;
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpop\tsb[in]\n");
              bufferIndex++;
            }
            else{
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);
              printf("\tadd\n\tpop\tin\n\tpop\tsb[in]\n");
            }
            break;
        case ASSIGN_ARR2:
            ex(p->opr.op[3]);
            ex(p->opr.op[1]);         /* first index */
            if(insideProc){
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n\tmul\n", arrayDimensions[i].y);
                  bufferIndex++;
                  break;
                }
              }
              ex(p->opr.op[2]);       /* second index */
              sprintf(buffer[bufferIndex], "\tadd\n"); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpop\tsb[in]\n"); bufferIndex++;
            }
            else{
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  printf("\tpush\t%d\n\tmul\n", arrayDimensions[i].y);
                  break;
                }
              }
              ex(p->opr.op[2]);            /* second index */
              printf("\tadd\n");
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);      /* address of the start of the array */
              printf("\tadd\n");
              printf("\tpop\tin\n\tpop\tsb[in]\n");
            }
            break;
        case ASSIGN_ARR3:
            ex(p->opr.op[4]);         /* calculate expression value */
            ex(p->opr.op[1]);         /* first index */
            // insideProc = true;
            if(insideProc){
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n\tpush\t%d\n\tmul\n\tmul\n", arrayDimensions[i].y, arrayDimensions[i].z);
                  bufferIndex++;
                  sprintf(buffer[bufferIndex], "\tpush\t%d\n", arrayDimensions[i].z);
                  bufferIndex++;
                  break;
                }
              }
              ex(p->opr.op[2]);         /* second index */
              sprintf(buffer[bufferIndex], "\tmul\n\tadd\n"); bufferIndex++;
              ex(p->opr.op[3]);         /* third index */
              sprintf(buffer[bufferIndex], "\tadd\n"); bufferIndex++;
              sprintf(buffer[bufferIndex], "\tpush\tfp[%d]\n", variableFPs[p->opr.op[0]->id.index]); bufferIndex++;   // address of the pass in array
              sprintf(buffer[bufferIndex], "\tadd\n\tpop\tin\n\tpop\tsb[in]\n"); bufferIndex++;
            }
            else{
              for(int i=0;i<numOfArr;i++){
                if(arrayDimensions[i].aind == p->opr.op[0]->id.index){
                  printf("\tpush\t%d\n\tpush\t%d\n\tmul\n\tmul\n", arrayDimensions[i].y, arrayDimensions[i].z);
                  printf("\tpush\t%d\n", arrayDimensions[i].z);
                  break;
                }
              }
              ex(p->opr.op[2]);       /* second index */
              printf("\tmul\n\tadd\n");
              ex(p->opr.op[3]);       /* third index */
              printf("\tadd\n");
              printf("\tpush\t%d\n", variableSPs[p->opr.op[0]->id.index]);      /* address of the start of the array */
              printf("\tadd\n");
              printf("\tpop\tin\n\tpop\tsb[in]\n");
            }
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
            case '+':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tadd\n");
                bufferIndex++;
                FPoffset--;
              }
              else{
                printf("\tadd\n");
                currentSP -= 1;
              }
              break;
            case '-':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tsub\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tsub\n");
                currentSP -= 1;
              }
              break;
            case '*':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tmul\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tmul\n");
                currentSP -= 1;
              }
              break;
            case '/':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tdiv\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tdiv\n");
                currentSP -= 1;
              }
              break;
            case '%':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tmod\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tmod\n");
                currentSP -= 1;
              }
              break;
            case '<':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompLT\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompLT\n");
                currentSP -= 1;
              }
              break;
            case '>':
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompGT\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompGT\n");
                currentSP -= 1;
              }
              break;
            case GE:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompGE\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompGE\n");
                currentSP -= 1;
              }
              break;
            case LE:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompLE\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompLE\n");
                currentSP -= 1;
              }
              break;
            case NE:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompNE\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompNE\n");
                currentSP -= 1;
              }
              break;
            case EQ:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tcompEQ\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tcompEQ\n");
                currentSP -= 1;
              }
              break;
      	    case AND:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tand\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tand\n");
                currentSP -= 1;
              }
              break;
      	    case OR:
              if(insideProc){
                sprintf(buffer[bufferIndex], "\tor\n");
                FPoffset--;
                bufferIndex++;
              }
              else{
                printf("\tor\n");
                currentSP -= 1;
              }
              break;

            }
        }
    }
    return 0;
}

void clearFrame(int FPoffset){
  /*
  sprintf(buffer[bufferIndex], "\tpop\tin\n");
  bufferIndex++;
  for(int i=0;i<FPoffset-1;i++){
    sprintf(buffer[bufferIndex], "\tpop\tsp\n");
    bufferIndex++;
  }
  sprintf(buffer[bufferIndex], "\tpush\tin\n");
  bufferIndex++;
  */
}
