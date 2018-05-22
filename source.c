#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char t[15][15][5][7];
int tot1=0;
int tot2=0;
int tcount=0;

struct node
{
  int letter;//letter printf("%c",x) to get letter
  int index;//index value
  int count;//occurrences
  int score;//score of each letter
  struct node *next;
};



typedef struct tnode
 {

     char word[20];
     struct tnode *left,*right;

 }tnode;

struct node *first=NULL;
struct node*temp=NULL;
struct tnode *head=NULL;

char ply[10];
char arr[10];


tnode * createNode(char *word) {
        tnode *newnode;
        newnode = (tnode*)malloc(sizeof(tnode));
        strcpy(newnode->word, word);

        newnode->left = newnode->right = NULL;
        return newnode;
  }

void insert_tree(char *word)
{
        tnode *parent = NULL, *current = NULL, *newnode = NULL;
        int res = 0;
        if (!head) {
                head = createNode(word);
                return;
        }
        for (current = head; current !=NULL;
           current = (res > 0) ? current->right : current->left) {
                res = strcasecmp(word, current->word);
                if (res == 0) {
                        printf("Duplicate entry!!\n");
                        return;
                }
                parent = current;
        }
        newnode = createNode(word);
        res > 0 ? (parent->right = newnode) : (parent->left = newnode);
        return;
  }
int search_tree(char *str) {
        tnode *temp = NULL;
        int flag = 0, res = 0;
        if (head == NULL) {
                //printf("Binary Search Tree is out of station!!\n");
                //return;
        }
        temp = head;
        while (temp) {
                if ((res = strcasecmp(temp->word, str)) == 0) {
                        return 0;

                        flag = 1;
                        break;
                }
                temp = (res > 0) ? temp->left : temp->right;
        }
        if (!flag)
            return 1;
                //printf("Search Element not found in Binary Search Tree\n");
        //return;
  }

void create_list(struct node**f)
{
  char ch[20];
  int l,i,ctr,scr;
  char *tok;

  FILE *fp;
  fp=fopen("letters1.csv","r");

    if(fp)
    {
        while(fgets(ch,100,fp))
        {
            temp=(struct node*)malloc(sizeof(struct node));

            tok=strtok(ch,",");
            i=atoi(tok);
            temp->index=i;
            tok=strtok(NULL,",");
            l=atoi(tok);
            temp->letter=l;
            tok=strtok(NULL,",");
            ctr=atoi(tok);
            temp->count=ctr;
            tok=strtok(NULL,",");
            scr=atoi(tok);
            temp->score=scr;

            temp->next=(*f);
            *f=temp;
          }
     }
     else
     {
        printf("error\n");
        exit(1);
     }
//
//    //to display the contents of the list
//    struct node *p=*f;
//    while((p)!=NULL)
//    {
//        printf("%c--",p->letter);
//        p=p->next;
//    }

    for(i=0;i<10;i++)
    {
        ply[i]=0;
    }

    printf("\n\n");
    fclose(fp);
}

void random(int x)
{
    int i;
    srand(time(NULL)+i);
    for(i=0;i<x;i++)
    {
        label:
            {
                int num=rand()%26;
                //printf("%d\n",num);

                int n=traversal(&first,num);
                if(n==0)
                {
                    if(tcount==100)
                    {
                        printf("tiles are empty\n");
                        return;
                    }
                    //printf("**no letters left for %d**\n",num);
                    goto label;
                }
                else
                {
                    insert(ply,n);
                    tcount++;
                }
            }
    }

    display(ply);

}
int traversal(struct node **p,int c)
{
   struct node *q,*prev;
    q=*p;
    while((q!=NULL) && (c!=q->index))
    {
        prev=q;
        q=q->next;
    }
    if((q!=NULL)&&(c==q->index))
    {
        if(q->count==0)
        {
            //printf("count of %c is 0\n",q->letter);
            return 0;
        }
        else
        {
            q->count--;
            return (q->letter);
        }

    }
}



int search_score(struct node **p,int c)
{
   struct node *q,*prev;
    q=*p;
    while((q!=NULL) && (c!=q->letter))
    {
        prev=q;
        q=q->next;
    }
    if((q!=NULL)&&(c==q->letter))
    {
        //printf("score of %c=%d\n",q->letter,q->score);
        return (q->score);
    }
}
void insert(char *a,int x)
{
    int i=0;

    while(a[i]!=0)
        i++;
    a[i]=x;

}

void display(char *a)
{
    int i=0;
    printf("\ntiles used=%d\n",tcount);
    printf("\n               player1 score:%d\n               player2 score:%d\n",tot1,tot2);
    printf("\n       ");
    for(i=0;i<10;i++)
        printf(" %c  ",ply[i]);
    printf("\n\n");
}


int check(char *in)
{
    char ch[100];
    FILE *fp;
    fp = fopen("words2.txt","r");
    if (fp== NULL)
    {
        printf("can not open file \n");
        return 1;
    }

    while(!feof(fp))
    {
        fscanf(fp,"%s",ch);
        if( strcmp(ch,in) == 0 )
            return 1;
    }
    fclose(fp);
    return 0;

}

void create_table()
{
    int i,j,r1,r2,count=1;

    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {

            for(r1=0;r1<5;r1++)
            {
                for(r2=0;r2<7;r2++)
                {
    //triple word score
                    if((r1==0 || r1==4)&&(((i==0) && ((j==0)||(j==7)||(j==14))) || ( (i==7) && ((j==0)||(j==7)||(j==14)) )  || (  (i==14) && ((j==0)||(j==7)||(j==14)) )    ))
                        t[i][j][r1][r2]='+';
                    else
                    if((r2==0 || r2==6)&&(((i==0) && ((j==0)||(j==7)||(j==14))  ) || ( (i==7) && ((j==0)||(j==7)||(j==14)) )  || (  (i==14) && ((j==0)||(j==7)||(j==14)) )))
                        t[i][j][r1][r2]='+';
                    else if( ((r1==2)&&(r2==3))&&( ((i==0) && ((j==0)||(j==7)||(j==14))  ) || ( (i==7) && ((j==0)||(j==7)||(j==14)) )  || (  (i==14) && ((j==0)||(j==7)||(j==14)) ) ))
                            t[i][j][r1][r2]='3';


    //double word score

                    else if(  ((r1==0 || r1==4))  &&   ( ((  (i<5)&&(i>0)  ) && (( j==i)||(j==(14-i) )) )  ||  ( ((j<5)&&(j>0)&&(i==(14-j))) || ( ((i==10)&&(j==10) ) || ((i==13)&&(j==13)) || ((i==12)&&(j==12)) || ((i==11)&&(j==11)) ))))
                        t[i][j][r1][r2]='+';
                    else if( ((r2==0) || (r2==6)) &&  ( ((  (i<5)&&(i>0)  ) && (( j==i)||(j==(14-i) )) )  ||  ( ((j<5)&&(j>0)&&(i==(14-j))) || ( ((i==10)&&(j==10) ) || ((i==13)&&(j==13)) || ((i==12)&&(j==12)) || ((i==11)&&(j==11))))))
                        t[i][j][r1][r2]='+';
                    else if(   ((r1==2)&&(r2==3))  &&    ( ((  (i<5)&&(i>0)  ) && (( j==i)||(j==(14-i) )) )  ||  ( ((j<5)&&(j>0)&&(i==(14-j))) || ( ((i==10)&&(j==10) ) || ((i==13)&&(j==13)) || ((i==12)&&(j==12)) || ((i==11)&&(j==11)) ))))
                        t[i][j][r1][r2]='2';



    //double letter places

                    else
                    if(  ((r1==0 || r1==4)) && (((i==0)&&((j==3)||(j==11))) || ((i==2)&&((j==6)||(j==8))) || ((i==3)&&((j==7)||(j==14))) || ((i==6)&&((j==6)||(j==8)||(j==12))) || ((i==7)&&(j==11)) || ((i==8)&&((j==12)||(j==8)))  || ((i==11)&&(j==14)))  )
                        t[i][j][r1][r2]='*';
                    else
                    if(  ((r2==0) || (r2==6)) && (((i==0)&&((j==3)||(j==11))) || ((i==2)&&((j==6)||(j==8))) || ((i==3)&&((j==7)||(j==14))) || ((i==6)&&((j==6)||(j==8)||(j==12))) || ((i==7)&&(j==11)) || ((i==8)&&((j==12)||(j==8)))  || ((i==11)&&(j==14))) )
                        t[i][j][r1][r2]='*';
                    else
                    if(  ((r1==2)&&(r2==3)) && (((i==0)&&((j==3)||(j==11))) || ((i==2)&&((j==6)||(j==8))) || ((i==3)&&((j==7)||(j==14))) || ((i==6)&&((j==6)||(j==8)||(j==12))) || ((i==7)&&(j==11)) || ((i==8)&&((j==12)||(j==8)))  || ((i==11)&&(j==14))))
                        t[i][j][r1][r2]='2';

                    else
                    if(  ((r1==0 || r1==4)) && (((j==0)&&((i==3)||(i==11))) || ((j==2)&&((i==6)||(i==8))) || ((j==3)&&((i==7)||(i==14))) || ((j==6)&&((i==6)||(i==8)||(i==12))) || ((j==7)&&(i==11)) || ((j==8)&&((i==12)||(i==8)))  || ((j==11)&&(i==14)))  )
                        t[i][j][r1][r2]='*';
                    else
                    if(  ((r2==0) || (r2==6)) && (((j==0)&&((i==3)||(i==11))) || ((j==2)&&((i==6)||(i==8))) || ((j==3)&&((i==7)||(i==14))) || ((j==6)&&((i==6)||(i==8)||(i==12))) || ((j==7)&&(i==11)) || ((j==8)&&((i==12)||(i==8)))  || ((j==11)&&(i==14))) )
                        t[i][j][r1][r2]='*';
                    else
                    if(  ((r1==2)&&(r2==3)) && (((j==0)&&((i==3)||(i==11))) || ((j==2)&&((i==6)||(i==8))) || ((j==3)&&((i==7)||(i==14))) || ((j==6)&&((i==6)||(i==8)||(i==12))) || ((j==7)&&(i==11)) || ((j==8)&&((i==12)||(i==8)))  || ((j==11)&&(i==14))))
                        t[i][j][r1][r2]='2';


//double letter score

                    else
                    if( ((r1==0 || r1==4))&&((((i==5)||(i==9))&&((j==1)||(j==5)||(j==9)||(j==13)))||(((i==1)||(i==13))&&((j==5)||(j==9))))  )
                        t[i][j][r1][r2]='*';
                    else
                    if( ((r2==0) || (r2==6)) && ((((i==5)||(i==9))&&((j==1)||(j==5)||(j==9)||(j==13)))||(((i==1)||(i==13))&&((j==5)||(j==9)))) )
                        t[i][j][r1][r2]='*';
                    else
                    if( ((r1==2)&&(r2==3)) && ((((i==5)||(i==9))&&((j==1)||(j==5)||(j==9)||(j==13)))||(((i==1)||(i==13))&&((j==5)||(j==9)))) )
                        t[i][j][r1][r2]='3';


                    else
                    if(r1==0 || r1==4)
                        t[i][j][r1][r2]='.';
                    else
                    if(r2==0 || r2==6)
                        t[i][j][r1][r2]='.';
                    else
                        t[i][j][r1][r2]=0;




                }
            }
        }
    }
    display_table();

}
void display_table()
{
    int i,j,count=1,r1,r2;
    printf("        1      2      3      4      5      6      7      8      9     10     11     12     13     14     15\n");
    for(i=0;i<15;i++)
    {
        for(r1=0;r1<5;r1++)
        {
            if(count>=10 && r1==2)
            {
                printf("  %d ",count);
                count++;
            }
            else
                if((r1==2))
            {
                printf("  %d  ",count);
                count++;
            }


            else
            {
                printf("     ");
            }

            for(j=0;j<15;j++)
            {
                for(r2=0;r2<7;r2++)
                {
                    printf("%c",t[i][j][r1][r2]);
                }
            }
            printf("\n");
        }

    }
    printf("        1      2      3      4      5      6      7      8      9     10     11     12     13     14     15\n");
    //display(ply);
}


//-----------checking whether the letters entered are present in the randomly generated tiles

int check_letters(char *a,char *w)
{
    int i=0,j=0,count1=0;

    int b[10]={0,0,0,0,0,0,0,0,0,0};

    for(i=0;i<strlen(w);i++)
    {
        for(j=0;j<10;j++)
        {
            if(w[i]-32==a[j] && b[j]==0)    //----converts small letters to capital letters
            {
                count1++;
                b[j]=1;
                break;
            }
        }
    }
    if(count1==strlen(w))
    {
        //printf("all letters are present\n");
        return 1;
    }

    else
    {
        printf("few letters are missing\n");
        return 0;
    }


}


//----generates new letters only for the letters used to make word
void get_letters(char *a,char *w)
{
    int i=0,j,count1=0;
   int b[10]={0,0,0,0,0,0,0,0,0,0};

     for(i=0;i<strlen(w);i++)
    {
       // printf("w=%s\n",w);
        for(j=0;j<10;j++)
        {
            int var;
            if(w[i]-32==a[j] && b[j]==0)
            {
               ran: srand(time(NULL)+var);
                int num=rand()%26;
                //printf("random generated num=%d letter=%c\n",num,traversal(&first,num));
                int tra=traversal(&first,num);
                if(tra==0)
                {
                    var++;
                    goto ran;
                }
                else
                {
                    a[j]=tra;
                    b[j]=1;
                    tcount++;
                    break;
                }

            }
        }
    }
    display(a);
}


int search_places_hor(int r,int c,char *w,int x)
{
    int i=0,j=0,index=0,l=0;
    char left_word[7],right_word[7];
    arr[0]='\0';

    left_word[0]='\0';
    right_word[0]='\0';

    for(i=c;l<=strlen(w);i++)
    {
        if(t[r][i][2][3]>96 && t[r][i][2][3]<123)
        {
             arr[index]=t[r][i][2][3];
             arr[index+1]='\0';
        }
        else
        {
            arr[index]=w[l];
            arr[index+1]='\0';
            l++;
        }
        index++;
    }
    i=0;

    int pre_r=c-1,next_r=c+strlen(arr);
    while((pre_r>=0) && (t[r][pre_r][2][3]>96 && t[r][pre_r][2][3]<122))
    {
        left_word[i]=t[r][pre_r][2][3];
        left_word[i+1]='\0';
        i++;
        pre_r--;
    }
    j=0;
    while((next_r<=14) && (t[r][next_r][2][3]>96 && t[r][next_r][2][3]<123))
    {
        right_word[j]=t[r][next_r][2][3];
        right_word[j+1]='\0';
        j++;
        next_r++;
    }



    char new_word[20];
    strcpy(new_word,left_word);
    strcat(new_word,arr);
    strcat(new_word,right_word);

    int lscr=0,rscr=0;
    if(strlen(left_word)!=0)
    {
        int k=0;
        for(k=0;k<strlen(left_word);k++)
            lscr=lscr+search_score(&first,left_word[k]-32);
    }
    if(strlen(right_word)!=0)
    {
        int k=0;
        for(k=0;k<strlen(right_word);k++)
            rscr=rscr+search_score(&first,right_word[k]-32);
    }

   // printf("new word=%s\n",new_word);

    if(check(new_word) && search_tree(new_word))
    {
        //printf("valid word\n");
        if(x==1)
            tot1=tot1+lscr+rscr;
        else
            tot2=tot2+lscr+rscr;
         insert_tree(new_word);
         return 1;
    }

    else
    {
        printf("invalid word\n");
        return 0;
    }



}


int search_places_ver(int r,int c,char *w,int x)
{
    int i=0,j=0,index=0,l=0;
    char top_word[7],bot_word[7];
    arr[0]='\0';
    top_word[0]='\0';
    bot_word[0]='\0';


    for(i=r;l<strlen(w);i++)
    {
        if(t[i][c][2][3]>96 && t[i][c][2][3]<123)
        {
             arr[index]=t[i][c][2][3];
             arr[index+1]='\0';
        }
        else
        {
            arr[index]=w[l];
            arr[index+1]='\0';
            l++;
        }
        index++;
    }
    i=0;
    int pre_c=r-1,bot_c=r+strlen(w);
    while((pre_c>=0) && (t[pre_c][c][2][3]>96 && t[pre_c][c][2][3]<123))
    {
        top_word[i]=t[pre_c][c][2][3];
        top_word[i+1]='\0';
        i++;
        pre_c--;
    }
    j=0;
    while((bot_c<=14) && (t[bot_c][c][2][3]>96 && t[bot_c][c][2][3]<123))
    {
        bot_word[j]=t[bot_c][c][2][3];
        bot_word[j+1]='\0';
        j++;
        bot_c++;
    }

    char new_word[20];
    strcpy(new_word,top_word);
    strcat(new_word,arr);
    strcat(new_word,bot_word);
    int lscr=0,rscr=0;

    if(strlen(top_word)!=0)
    {
        int k=0;
        for(k=0;k<strlen(top_word);k++)

            lscr=lscr+search_score(&first,top_word[k]-32);

    }
    if(strlen(bot_word)!=0)
    {
        int k=0;
        for(k=0;k<strlen(bot_word);k++)

            rscr=rscr+search_score(&first,bot_word[k]-32);
    }

   // printf("new word=%s\n",new_word);
    if(check(new_word) && search_tree(new_word))
    {
       // printf("valid\n");
       if(x==1)
            tot1=tot1+lscr+rscr;
        else
            tot2=tot2+lscr+rscr;
        insert_tree(new_word);
        return 1;
    }
    else
    {
        printf("invalid\n");
        return 0;

    }

}

void change(int r,int c)
{
    int i;
    for(i=0;i<5;i++)
    {
        t[r][c][i][0]=0;
        t[r][c][i][6]=0;
    }
    for(i=0;i<7;i++)
    {
        t[r][c][0][i]=0;
        t[r][c][4][i]=0;
    }
}
void play(int x)
{
    char rc[5],w[15],dir;
    int count=0;
    int i,scr1,extra_word=0;
    while(x)
    {
        if(x==1)
            printf("PLAYER 1:\n");
        else
            printf("PLAYER 2:\n");


        int extra_word=1,scr1=0;
        printf("Enter row/colm where you want to insert the word(eg:12,12)\n");
        scanf("%s",rc);
        int r=atoi(strtok(rc,","))-1;
        int c=atoi(strtok(NULL,""))-1;

            if((r<0 || r>14)||(c<0 || c>14))
            {
                system("cls");
                display_table();
                display(ply);
                printf("enter valid row,column\n");
                continue;
            }

            fflush(stdin);
            printf("Horizontal or Vertical(H or V)\n");
            scanf("%c",&dir);

            if(dir=='H' || dir=='h')
            {

                printf("enter the word\n");
                scanf("%s",w);
                if((c+(strlen(w)-1))>14)
                {

                    system("cls");
                    display_table();
                    display(ply);
                    printf("cannot form it horizontally\n");
                    continue;
                }
                fflush(stdin);
                int present=check_letters(ply,w);

                int valid=search_places_hor(r,c,w,x);

                if((valid==1) && (present==1))
                {
                    for(i=0;i<strlen(arr);i++)
                    {
                        int extra_letter=1;
                        if(t[r][c+i][0][0]=='+')   //triple or double word score
                        {
                            extra_word=t[r][c+i][2][3]-'0';
                            if(extra_word<=3 && extra_word>=1)
                                scr1=search_score(&first,arr[i]-32)+scr1;
                        }
                        else if(t[r][c+i][0][0]=='*')    //triple or double letter score
                        {
                            extra_letter=t[r][c+i][2][3]-'0';
                            if(extra_letter<=3 && extra_letter>=1)
                            scr1=(search_score(&first,arr[i]-32)*extra_letter)+scr1;
                        }
                        else
                        {
                            scr1=search_score(&first,arr[i]-32)+scr1;
                        }
                        t[r][c+i][2][3]=arr[i];

                        change(r,c+i);

                    }
                    if(x==1)
                        tot1=tot1+(scr1*extra_word);
                    else
                        tot2=tot2+(scr1+extra_word);
                    get_letters(ply,w);
                    system("cls");
                    display_table();
                    display(ply);

                }
                else
                {
                    count++;
                    if(count==3 && x==1)
                    {

                        count=0;
                        system("cls");
                        display_table();
                        display(ply);
                        printf("You lost your chance\n");
                        play(2);
                    }
                    else if(count==3 && x==2)
                    {


                        count=0;
                        system("cls");
                        display_table();
                        display(ply);
                        printf("You lost your chance\n");
                         play(1);
                    }

                    else
                    {

                        system("cls");
                        display_table();
                        display(ply);
                        printf("Cannot form this word\n");
                        continue;
                    }
                }

            }
            else if(dir=='V' || dir=='v')
            {

                printf("enter the word\n");
                scanf("%s",w);

                if((r+(strlen(w)-1))>14)
                {

                    system("cls");
                    display_table();
                    display(ply);
                    printf("cannot form it vertically\n");
                    continue;
                }

                fflush(stdin);

                int present=check_letters(ply,w);
                int valid=search_places_ver(r,c,w,x);


                if((valid==1) && (present==1))
                {
                    for(i=0;i<strlen(arr);i++)
                    {
                        int extra_letter=1;
                        if(t[r+i][c][0][0]=='+')   //triple or double word score
                        {
                            extra_word=t[r+i][c][2][3]-'0';
                            if(extra_word<=3 && extra_word>=1)
                                scr1=search_score(&first,arr[i]-32)+scr1;

                        }
                        else if(t[r+i][c][0][0]=='*')    //triple or double letter score
                        {
                            extra_letter=t[r+i][c][2][3]-'0';
                            if(extra_letter<=3 && extra_letter>=1)
                                scr1=(search_score(&first,arr[i]-32)*extra_letter)+scr1;

                        }
                        else
                        {
                            scr1=search_score(&first,arr[i]-32)+scr1;
                            printf("scr1 in else=%d\n",scr1);
                        }
                        t[r+i][c][2][3]=arr[i];

                         change(r+i,c);

                    }

                    if(x==1)
                        tot1=tot1+(scr1*extra_word);
                    else
                        tot2=tot2+(scr1*extra_word);
                    get_letters(ply,w);
                    system("cls");
                    display_table();
                    display(ply);
                }
                else
                {

                    count++;
                    if(count==3 && x==1)
                    {
                        count=0;
                        system("cls");
                        display_table();
                        display(ply);
                        printf("You lost your chance\n");
                        play(2);

                    }
                    else if(count==3 && x==2)
                    {
                        count=0;
                        system("cls");
                        display_table();
                        display(ply);
                        printf("You lost your chance\n");
                        play(1);
                    }
                    else
                    {
                        system("cls");
                        display_table();
                        display(ply);
                        printf("Cannot form this word\n");
                        continue;
                    }
                }
            }
            else
            {
                 system("cls");
                 display_table();
                 display(ply);
                 printf("enter valid direction\n\n");
                 continue;
            }

            if(x==1)
                play(2);
            else
                play(1);
    }



}
int main()
{
    create_table();
    create_list(&first);
    random(10);
    play(1);
    return 0;
}
