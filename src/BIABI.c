/*
BIABI (BIABI is a brainfuck interpreter)
Copyright (C) 2008  Pit Gennari
pit.gennari@49-6-dev.net        www.49-6-dev.net

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include <stdio.h>

unsigned char code[2500000], p[30000], c;
int lps[30000], n, in=1, endpos=-1, pos=-1, lpc=0, bc=0, re=0;
   
int main(int argc, char *argv[])        
{      
    if(argc < 2) argv[1] = "code.b";
    FILE *fle = fopen(argv[1], "r");         
    if(!fle) printf("could not open file"); 
    else                              
    {
        while((in = fgetc(fle)) != EOF)                       
        {
            if(in>42 && in<47 || in=='>' || in=='<' || in=='[' || in==']') code[endpos+=1] = in;                                  
            if(in=='[' || in==']') bc+=92-in;
            if(bc < 0) re=1;
        }
        fclose(fle);                          
    }
    if(bc != 0) printf("%.f %c missed", sqrt(bc*bc), 92+(char)bc/(char)sqrt(bc*bc));                           
    else if(re == 1) printf("range error"); 
    if(bc != 0 || re > 0 || in == 1) pos = endpos = getchar();
    
    for(n = 30000; n > 0; n--) p[n-1] = 0;  
    while(pos < endpos)                     
    {                   
        if((c=code[pos+=1]) == '[')
        {
            if(p[n] == 0) lps[lpc+=1] = 0;
            else lps[lpc+=1] = pos;
        }           
        else if(c == ']')
        {
            if(p[n] != 0) pos = lps[lpc];
            if(p[n] == 0) lpc--;
        }  
        else if(lpc == 0 || lps[lpc] != 0)
        {
            switch(c)                          
            {
                case('>'):n++;if(n==30000)n=0;break;       
                case('<'):n--;if(n==-1)n=29999;break;                     
                case('+'):p[n]++;break;                   
                case('-'):p[n]--;break;                      
                case('.'):putchar(p[n]);break;                    
                case(','):if((in=getchar())!=EOF)p[n]=in;break;
            }   
        }                                      
    }
    return 0;                               
}
    

