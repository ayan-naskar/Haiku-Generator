#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#include<time.h>

#define si(n) scanf("%d",&n)
#define sf(n) scanf("%f",&n)
#define sd(n) scanf("%lf",&n)
#define sc(n) scanf("%c",&n)
#define su(n) scanf("%u",&n)

#define pi(n) printf("%d\n",n)
#define pf(n) printf("%f\n",n)
#define pd(n) printf("%lf\n",n)
#define pc(n) printf("%c\n",n)
#define pu(n) printf("%u\n",n)

#define PI 3.1415926535897932384626
#define fo(i,n) for(i=0;i<n;i++)

#define prr(p,n) p=(int*)malloc(sizeof(int)*n)
#define srr(p,n) p=(char*)malloc(sizeof(char)*n)
#define ll long long
#define ui unsigned int



struct node{
	char word[30];
	struct node *next;
};

struct node *ar[8];

void putWordInPlace(int n, char *p){
	int i;
	struct node *q=ar[n],*qq,*wor=(struct node*)malloc(sizeof(struct node));
	wor->next=NULL;
	strcpy(wor->word,p);
	//puts(wor->word);
	if(q==NULL){
		ar[n]=wor;
	}
	else{
		while(q!=NULL){
			if(strcmp(wor->word,q->word)==0)
				return;
			qq=q;
			q=q->next;
		}
		qq->next=wor;
	}
	//while(q->next!=NULL)
	//	q=q->next;
	//q->next=wor;
	//puts(ar[n]->word);
}

void showList(){
	int i;
	puts("The words int the list are:");
	struct node *p;
	fo(i,7){
		p=ar[i+1];
		printf("Syllable %d: ",i+1);
		if(p==NULL)
			printf("NULL");
		while(p!=NULL){
			//puts(p->word);
			printf("%s\t",p->word);
			p=p->next;
		}
		puts("\n\n");
	}
}

char* getWord(int n){// bhul ekhane ache, i ta 0 hoche tai divite korte prob hoche
	int i=0,j;
	//puts("AAAAA");
	//pi(n);
	struct node *p;
	p=ar[n];
	while(p!=NULL){
		p=p->next;
		i++;
	}
	//pi(i);
	j=rand()%i;
	//puts("BBBB");
	p=ar[n];
	fo(i,j) p=p->next;
	//puts(p->word);
	return p->word;
}

char* getLine(int n){
	//puts("start");
	struct node *p;
	int index=0;
	char *line=(char*)malloc(sizeof(char)*100),*str;
	int len=rand()%n+1;
	strcpy(line,"");
	while(true){
		//printf("\nn=%d\tlen=%d\n",n,len);
		str=getWord(len);
		//puts(str);
		strcat(line,str);
		strcat(line," ");
		index+=strlen(str)+1;
		n=n-len;
		if(n==0) break;
		len=rand()%n+1;
		//puts(line);
		if(len==0) break;
	}
	line[index-1]='\0';
	//puts("end");
	//puts(line);
	return line;
}

void makeList(){
	FILE *op=fopen("syllable_words.txt","r");
	int i=1,j=0;
	char *wor=(char*)malloc(sizeof(char)*30),ch;
	while(fscanf(op,"%c",&ch)!=EOF){
		if(ch==' '){
			wor[j]='\0';
			putWordInPlace(i,wor);
			//puts(wor);
			j=0;
		}
		else if(ch=='\n'){
			fscanf(op,"%c",&ch);
			i++;
		}
		else{
			wor[j]=ch;
			j++;
		}		
	}
}

bool isPresentIn(char a,char *p){//helper function to check vowelity
	int i=0;
	while(p[i]!='\0'){
		if(p[i]==a)
			return true;
		i++;
	}
	//puts(p);
	//pc(a);
	return false;
}

int countSyllable(char *word){
	int i=0,j,flagg=0;
	float cal;
	int consecutiveVOWEL=0,numOfSyllable=0,fl=0;

	char vowel[7]="aeiou";
	if(word[0]!='y')
		strcat(vowel,"y");

	while(flagg==0){
		if(word[i]=='\0'){
			flagg=1;
		}

		if(word[i]=='e' && word[i+1]=='\0' && i>2 && word[i-1]!='l'){
			i++;
			continue;
		}
		else if((word[i-1]=='t' || word[i-1]=='s') && word[i]=='i' && word[i+1]=='o' && word[i+2]=='n'){
			numOfSyllable++;
			consecutiveVOWEL=0;
			fl=0;
			i+=3;
			continue;
		}
		else if(word[i]=='s' && word[i+1]=='m' && word[i+2]=='\0'){
			numOfSyllable++;
			break;
		}
		else if(word[i]=='i' && isPresentIn(word[i+1],vowel)){
			numOfSyllable++;
		}
		if(!isPresentIn(word[i],vowel)){
			if(fl==1){
				fl=0;
				cal=(round(((float)consecutiveVOWEL/2.0+0.111)));
				numOfSyllable+=(int)cal;
				//pf(cal);
				//pi(consecutiveVOWEL);
				consecutiveVOWEL=0;
			}
		}
		else{
			consecutiveVOWEL++;
			fl=1;
		}
		//pi(i);
		i++;
	}
	if(numOfSyllable==0)
		return 1;
	else return numOfSyllable;
}

/*bool isSpecial(char *a, char *b){
	char a[]
}*/

bool mightRhyme(char *a, char *b){
	int f=0,an,bn,i;
	//puts("start");
	if(strcmp(a,b)==0)
		return false;
	if(strlen(a)<3 || strlen(b)<3)
		return false;
	//else if(isSpecial(a,b))	return true;
	an=strlen(a);
	bn=strlen(b);
	fo(i,3){
		if(a[an-1]==b[bn-1])
			f++;
		an--;
		bn--;
	}
	//puts("end");
	if(f==3)
		return true;
	else return false;
}

void randWordThatRhymes(){
	int a=rand()%7+1,b=rand()%7+1;
	char *p,*q;
	p=getWord(a);
	q=getWord(b);
	while(!mightRhyme(p,q)){
		randWordThatRhymes();
		return;
	}
	//printf("%d",mightRhyme(p,q));
	printf("\n");
	puts(p);
	puts(q);
}

bool okay(char a){
	if((a>='a' && a<='z')||(a=='\''))
		return true;
	return false;
}

void makeListFromWordFile(char *ch){
	int syllableCount,j=0;
	char word[30],a;
	FILE *f=fopen(ch,"r");
	if(f==NULL){
		printf("\nError Openning File!");
		return;
	}
	for(a=fgetc(f);a!=EOF;a=fgetc(f)){
		a=tolower(a);
		if(okay(a)){
			word[j]=a;
			j++;
		}
		else if(a==' ' || a=='\n'){
			word[j]='\0';
			//puts(word);
			syllableCount=countSyllable(word);
			putWordInPlace(syllableCount,word);
			j=0;
		}
	}
}

char* getLastWord(char *s){
	//puts("start");
	char *a=(char*)malloc(sizeof(char)*50),b;
	int i=0,j=0,k;
	fo(k,50)a[k]='\0';
	//puts(s);
	//pi(strlen(s));
	//s[strlen(s)-1]='\0';
	while(s[i]!='\0'){
		if(s[i]!=' '){
			a[j]=s[i];
			j++;
		}
		else{
			fo(k,50)a[k]='\0';
			//puts(a);
			//pi(strlen(a));
		 	j=0;
		}
		i++;
	}
	i=0;
	return a;
}



char* haikuGenerate(){
	char A[50],*B,C[50],*str;
	str=(char*)malloc(150*(sizeof(char)));
	strcpy(A,getLine(5));
	char *q=getLastWord(A);
	//puts(q);
	B=getLine(7);
	//strcpy(B,getLine(7));
	while(!mightRhyme(getLastWord(B),q)){
		//puts("s");
		B=getLine(7);
		//strcpy(B,getLine(7));
		//puts("e");
		//puts(B);
	}
	strcpy(C,getLine(5));
	while(!mightRhyme(getLastWord(C),q)){
		strcpy(C,getLine(5));
	}
	strcpy(str,A);
	strcat(str,"\n");
	strcat(str,B);
	strcat(str,"\n");
	strcat(str,C);
	return str;
}

int main(){
	int i,j,n,t,a,b;
	char qqqq[30]="wordlist.txt";
	fo(i,8) ar[i]=NULL;
	srand(time(0));
	makeListFromWordFile(qqqq);
	//makeList();
	showList();
	//printf("Working\n");
	//puts(getWord(4));
	//printf("--------------\n");
	//puts(getLine(5));
	//puts(getLine(7));
	//puts(getLine(5));
	//puts("yes");
	//strcpy(qqqq,getWord(7));
	//puts(qqqq);
	//printf("here=%d",countSyllable(qqqq));
	//randWordThatRhymes();
	puts(haikuGenerate());
}