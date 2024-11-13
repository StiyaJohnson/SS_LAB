#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *deftabself,*argtabself,*namtabself,*inputself,*outself;
    char argument[25],label[25],macroname[25],mnemonic[25],operand[25],defmnemonic[25],defoperand[25];
    int position=1,argument_position[25],pos_arg,i,j;

    deftabself=fopen("deftabself.txt","w+");
    argtabself=fopen("argtabself.txt","w+");
    namtabself=fopen("namtabself.txt","w+");
    inputself=fopen("inputself.txt","r");
    outself=fopen("outself.txt","w+");
    fscanf(inputself,"%s\t%s\t%s",label,mnemonic,operand);

    while(strcmp(mnemonic,"END")!=0)
    {
        if(strcmp(mnemonic,"MACRO")==0)
        {
            fprintf(namtabself,"%s\n",label);
            fseek(namtabself,SEEK_SET,0);
            fprintf(deftabself,"%s\t%s\n",label,operand);

            char *token=strtok(operand,",");
            while(token!=NULL)
            {
                argument_position[position++]=token[1];
                token=strtok(NULL,",");
            }
            fscanf(inputself,"%s\t%s\t%s",label,mnemonic,operand);

            while(strcmp(mnemonic,"MEND")!=0)
            {
                if(operand[0]=='&')
                {
                    for(j=1;j<=position;j++)
                    {
                        if(argument_position[j]==operand[1])
                        {
                            pos_arg=j;
                        }
                    }
                    sprintf(operand,"?%d",pos_arg);

                    fprintf(deftabself,"%s\t%s\n",mnemonic,operand);

                    fscanf(inputself,"%s\t%s\t%s",label,mnemonic,operand);
                }
            }

            fprintf(deftabself,"%s",mnemonic);

        }

        else
        {
            fscanf(namtabself,"%s",macroname);
            if(strcmp(mnemonic,macroname)==0)
            {
                int operandlength;
                operandlength=strlen(operand);

                for(i=0;i<operandlength;i++)
                {
                    if(operand[i]!=',')
                    {
                        fprintf(argtabself,"%c",operand[i]);
                    }
                    else
                    {
                        fprintf(argtabself,"\n");
                    }

                }

                fseek(deftabself,SEEK_SET,0);

                fprintf(outself,"**\t.%s\t%s\n",mnemonic,operand);

                fscanf(deftabself,"%s%s",defmnemonic,defoperand);

                fseek(argtabself,SEEK_SET,0);

                while(strcmp(defmnemonic,"MEND")!=0)
                {
                    if(defoperand[0]=='?')
                    {
                        long pos=defoperand[1]-'0';
                        for(i=1;i<=pos;i++)
                        {
                            fscanf(argtabself,"%s",argument);
                        }
                        fprintf(outself,"**\t%s\t%s\n",defmnemonic,argument);
                        fseek(argtabself,SEEK_SET,0);
                    }
                    else if(defoperand[0]!='&')
                    {
                        fprintf(outself,"**\t%s\t%s\n",defmnemonic,defoperand);
                    }
                    fscanf(deftabself,"%s%s",defmnemonic,defoperand);

                    
                }
            }
            else
            {
               fprintf(outself,"%s\t%s\t%s\n",label,mnemonic,operand);
            }
        }

        fscanf(inputself,"%s\t%s\t%s",label,mnemonic,operand);
    }

    fprintf(outself,"%s\t%s\t%s\n",label,mnemonic,operand);

    fclose(inputself);
    fclose(argtabself);
    fclose(deftabself);
    fclose(outself);
    fclose(namtabself);

    return 0;
}