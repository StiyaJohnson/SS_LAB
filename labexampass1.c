#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_duplicate(FILE *labexamsymtab,const char *label)
{
    char sym_label[25];
    int address;
    rewind(labexamsymtab);
    while(fscanf(labexamsymtab,"%s\t%s",sym_label,&address)!=EOF)
    {
        if(strcmp(sym_label,label)==0)
        {
            return 1;
        }
    }
    return 0;
}



int main()
{
    FILE *labexamsymtab,*labexaminter,*labexamoptab,*labexamlength,*labexaminput;
    char label[25],opcode[25],operand[25],code[25],mnemonics[25];
    int locctr,start;


    labexamoptab=fopen("labexamoptab.txt","r");
    labexamsymtab=fopen("labexamsymtab.txt","w+");
    labexaminput=fopen("labexaminput.txt","r");
    labexaminter=fopen("labexaminter.txt","w");
    labexamlength=fopen("labexamlength.txt","w");


    if(labexaminput==NULL ||labexaminter==NULL|| labexamlength==NULL||labexamoptab==NULL||labexamsymtab==NULL)
    {
        printf("unable to open one or more files\n");
        return 1;
    }

    fscanf(labexaminput,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        locctr=start;
        printf("the start is %d\n",start);
        fprintf(labexaminter,"%s\t%s\t%s\n",label,opcode,operand);
    }

    else
    {
        locctr=0;
    }

    fscanf(labexaminput,"%s\t%s\t%s",label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(labexaminter,"%d\t",locctr);
        if(strcmp(label,"**")!=0)
        {
            if(check_duplicate(labexamsymtab,label))
            {
                printf("error:duplicate label '%s' found\n",label);
                fclose(labexaminput);
                fclose(labexaminter);
                fclose(labexamlength);
                fclose(labexamoptab);
                fclose(labexamsymtab);
                return 1;
            }
            else
            {
                if(fprintf(labexamsymtab,"%s\t%d\n",label,locctr)<0)
                {
                    printf("failed to write\n");
                     fclose(labexaminput);
                    fclose(labexaminter);
                    fclose(labexamlength);
                    fclose(labexamoptab);
                    fclose(labexamsymtab);
                    return 1;
                }
            }
        }

        int opcode_found=0;
        rewind(labexamoptab);
        while(fscanf(labexamoptab,"%s\t%s",code,mnemonics)!=EOF)
        {
            if(strcmp(opcode,code)==0)
            {
                locctr+=3;
                opcode_found=1;
                break;
            }
        }

        if(!opcode_found)
        {
            if(strcmp(opcode,"WORD")==0)
            {
                locctr+=3;
            }
            else if(strcmp(opcode,"RESW")==0)
            {
                locctr+=3*atoi(operand);
            }
            else if(strcmp(opcode,"RESB")==0)
            {
                locctr+=atoi(operand);
            }
            else if(strcmp(opcode,"BYTE")==0)
            {
               if(operand[0]=='C')
               {
                locctr+=strlen(operand);
               }
               else if(operand[0]=='X')
               {
                locctr+=(strlen(operand)-3)/2;

               }
            }
        }
        fprintf(labexaminter,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(labexaminput,"%s\t%s\t%s",label,opcode,operand);


    }
    fprintf(labexaminter,"%s\t%s\t%s\n",label,opcode,operand);
    fprintf(labexamlength,"%d",locctr-start);
    printf("the length is %d\n",locctr-start);

                    fclose(labexaminput);
                    fclose(labexaminter);
                    fclose(labexamlength);
                    fclose(labexamoptab);
                    fclose(labexamsymtab);

        return 0;
}