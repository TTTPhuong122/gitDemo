#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int ERROR_STATE=100;
typedef int state;// kieu cac trang thai
typedef unsigned char *attri;// kieu cua thuoc tinh
typedef unsigned char *token; //kieu cua tu to
unsigned char *x;//xau vao x
unsigned int i=0;// vi tri cua ky tu doc trong xau x
unsigned char readchar(unsigned char *x){
//tra ve ky tu thu i
if(i<strlen(x)) return (*(x+i));
else return ('\0'); }
attri attribute(state s) {
// tra ve thuoc tinh tuong ung voi trang thai ket thuc
char *ch;
switch(s){
case 2: 
        ch="so sanh lon hon bang";break;
case 3: ch="dich phai"; break;
case 4: ch="so sanh lon hon"; break;
case 6: ch="so sanh nho hon bang";break;
case 7: ch="dich trai"; break;
case 8: ch="so sanh nho hon"; break;
case 10: ch="so sanh khong bang"; break;
case 11: ch="phu dinh"; break;
case 13: ch="so sanh bang"; break;
case 14: ch="gan"; break;
case 17: ch="cong bang"; break;
case 18: ch="tang 1"; break;
case 19: ch="cong"; break;
case 21: ch="tru bang"; break;
case 22: ch="giam 1"; break;
case 23: ch="tru"; break;
case 25: ch="nhan bang"; break;
case 26: ch="nhan"; break;
case 28: ch="chia bang"; break;
case 29: ch="chia"; break;
case 30: ch="chia lay du"; break;
default: ch="token ko duoc doan nhan(tt ko dung \0";
}
return ch; 

}
int nostar_end_state(state s){
//kiem tra trang thai s co phai la trang thai ket thuc khong sao ?
switch(s){
case 2:
case 3:
case 6:
case 7:
case 10:
case 13:
case 17:
case 18:
case 21:
case 22:
case 25:
case 28:
case 30: return 1;
default: return 0;
}
}
int star_end_state(state s){
//kiem tra trang thai s co phai la trang thai ket thuc sao ?
switch(s){
case 4:
case 8:
case 11:
case 14:
case 19:
case 23:
case 26:
case 29: return 1;
default: return 0;
}
}
state start_state_otherbrand(state s){
state start;
switch(s){
case 0: start=15; break;
case 15: start=ERROR_STATE;
}
return start;
}
int start_state(state s){
if ((s==0) || (s==15)) return 1; return 0;
}
//void catchar_in_token (unsigned char c, token* tk){
//// ghep them ky tu c vao cho tu to tk
// 
//    size_t len = strlen(tk);
//   
//    /* one for extra char, one for trailing zero */
//    unsigned char *temp = malloc(len + 1 + 1);
//
//    strcpy(temp, *tk);
//    temp[len] = c;
//    temp[len + 1] = '\0';
//    //printf("%s", temp);
//	free(*tk);
//	//*tk=temp;
//    strcpy(*tk , temp);
//    free(temp);
//}
void catchar_in_token (unsigned char c, token tk){
 //ghep them ky tu c vao cho tu to tk
 *(tk+strlen(tk)+1)='\0';// da thu va chay k dc
 *(tk+strlen(tk))=c;}
attri search_token (token tken){
// tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
attri tt;
state s=0;
int stop=0;
unsigned char c=readchar(x);

 while ((c==' ')&&(i<strlen(x))){
 i++;
 c=readchar(x);
 
 }
 

while (i<strlen(x)&&(!stop)){
switch(s){
case 0: if (c=='>') s=1;
else if (c=='<') s=5;
else if (c=='!') s=9;
else if (c=='=') s=12;
else s=start_state_otherbrand(s);
break;
case 1: if (c=='=') s=2;
else if (c=='>') s=3;
else s=4;
break;
case 5: if (c=='=') s=6;
else if (c=='<') s=7;
else s=8;
break;
case 9: if (c=='=') s=10;
else s=11;
break;
case 12: if (c=='=') s=13;
else s=14;
break;
case 15: if (c=='+') s=16;
else if (c=='-') s=20;
else if (c=='*') s=24;
else if (c=='/') s=27;
else if (c=='%') s=30;
else s=start_state_otherbrand(s);
break;
case 16: if (c=='=') s=17;
else if (c=='+') s=18;
else s=19;
break;
case 20: if (c=='=') s=21;
else if (c=='-') s=22;
else s=23;
break;
case 24: if (c=='=') s=25;
else s=26;
break;
case 27: if (c=='=') s=28;
else s=29;
break;
default: stop=1;
}
if (s==ERROR_STATE){
stop=1;
printf("loi tai ky tu thu %i",i);
*(tken)='\0'; }
else if (start_state(s));
else if (nostar_end_state(s)) {
catchar_in_token(c,tken);
i++; stop=1;
strcpy(tt,attribute(s));} 	
else if (star_end_state(s)){
strcpy(tt,attribute(s)); stop=1;}
else {
catchar_in_token(c,tken);

i++;
c=readchar(x);}
}
return tt;
}
void save_token_and_attribute(token tk,attri a){
//luu tru tk,a vao danh sach
printf("%s %s",tk,a);

}
int lexical_analysis(){
 attri a;
 token tk=malloc(100);
	a=search_token(tk);
save_token_and_attribute(tk,a);
free(tk);
if(*tk=='\0') return 0;
else return 1;
}
void test(token tk ){

*(tk+2)='\0';
*(tk+1)='b';

}



int main(){
	x=">= <=1 ==";
	while (i<strlen(x) &&	lexical_analysis()==1){};


   // token t_k="asdlas";
   
  //unsigned char* s=malloc(100);
  //*(s+0)='c';
  //*(s+1)='\0';
  //test(s);
 // catchar_in_token('c',&s);
  // tesst(&s);
       //strncat(s,&xx,1);
 //   *(s2+3)=x;
 //   *(s2+2)=y;
    
//nhap xau vao x
//printf("%c",readchar(s,1));
//printf("%s \n",attribute(4));
// catchar_in_token('c',s2);
// printf("%s", s2);

//catchar_in_token('c', &t_k);
//printf("%s", t_k);
//char * s;
//tesst(s);

//printf("\n %s",s);
return 0 ;
    
}


