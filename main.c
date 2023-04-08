#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node {
double data;
double timestamp;
struct node *next;
struct node *prev;
} node;

node* first0 , *last0;//lista in care se face citirea initiala(ramane neschimbata
node* first1 , *last1;
node* first2 , *last2;


void add(node** first, node** last, double data, double timestamp)
{
	node* p = (node*) malloc(sizeof(node));
	p->data = data;
	p->timestamp = timestamp;
		
	//lista e goala
	if ( (*first) == NULL)
	{
		(*first) = p;
		(*last) = p;
		p->prev = NULL;
		p->next = NULL;
	}
	
	//adaugare dupa ultimul element;
	else 
	{
		p->prev = (*last);
		(*last)->next = p;
		p->next = NULL;
		(*last) = p;
	}
}

void print_list(node** first)
{
	
	node* a = *first;
	while(a != NULL)
	{
	printf("%0.3lf _ %0.3lf \n", a->data, a->timestamp);
	a = a->next;
	}
}

void free_list(node** first, node** last)
{

	node* a;
	while( (*first) != NULL)
	{
		a = (*first);
		//printf("%0.3lf_ ",a->data);
		(*first) = (*first)->next;
		free(a); 	
	}
	printf("\n (eliberare memorie cu date nefolositoare) \n");
}

void copy_list (node** first_a, node** last_a,node** first_b, node** last_b)
{
	node *p = (*first_a);
	while (p != NULL)
	{
		add (&(*first_b), &(*last_b), p->data, p->timestamp);
		p = p->next;
	}
}

void remove_node_interior(node *p)
{
	node *a = p;
	p = p->prev;
	p->next = p->next->next;
	p->prev = p;
	free(a);
}

void show_options()
{
	
	printf("\n option 1 ___ eliminate sensor's reading errors");
	printf("\n option 2 ___ do a time uniformisation of the signal");
	printf("\n option 3 ___ print the state of the signal (processed signal)");
	printf("\n option 4 ___ read a new number on inputs and those values ");	
	printf("\n\n please enter you option: " );
}
double average(node* p)
{
    double s = 0.00;
    int k = 5;
    while(k != 0)
    {
        s = s + p->data;
        k--;
        p = p->next;
    }
    s=(double)s/5;
    return s;
}

double deviation(node* p, double ave)
{
    double s=0.00;
    int k=5;
    while(k!=0)
    {
        double spar=(p->data-ave)*(p->data-ave);
        s+=spar;
        k--;
        p=p->next;
    }
    s=(double)s/5;
    s=(double)sqrt(s);
    return s;
}


int main()
{
	first0 = NULL;
	last0 = NULL;
	first1 = NULL;
	last1 = NULL;
	first2 = NULL;
	last2 = NULL;
	
	int t ,option,n;
	double data, timestamp;
	printf("please enter number of inputs: ");
	scanf("%d",&n);
	for(t=0; t<=n-1; t++)
	{
		printf("\n please enter input no %d ( value timestamp ): ",t+1);
		scanf("%lf %lf", &data, &timestamp);
		add(&first0, &last0, data, timestamp);
	}
	copy_list(&first0, &last0, &first1, &last1);
	
	printf("\n there are a few posibilities to manipulate this signal");
	show_options();
	scanf("%d", &option);
	
	int input = 1;
	int continuation = 1;//daca faci alta operatie;
	int k = 0;//nr elem din lista 2
	
	do		
	{
		if (option == 1)//eliminare exceptii
		{
					
			int h, j;
			node *p;
			//consideram ca primele 2 si ultimele 2 elemente date date de senzor sunt corecte100%	
			for(h=2; h<=n-3; h++)
 	       {
    	        j = h-2;
	            p = first1;
            
        	     //mergem la inceputul secventei de 5 elemente
    	        while(j != 0)
	            {
                	p = p->next;
            	    j--;
        	    }
    	        float ave = 0.00, dev;
	            ave = average(p);
        	    dev = deviation(p,ave);
    	        int ii = 2;
	            //ajungem la mijlocul secventei de 5 elemente
            	while(ii != 0)
            	{
          	    	p = p->next;
        			ii--;
     	 		}		
            	//adaugam in lista 2 elementele care nu corespund conditiei
        	    //(primele 2 date si ultimele 2 sunt mereu corecte)
    	        if(! (ave-dev <= p->data && ave+dev >= p->data) )
	                add(&first2, &last2, p->data, p->timestamp);
	        }
			p = first2;
			node *q, *del;
			
			while (p != NULL)
			{
				q = first1;
				while(q != NULL)
					{
						if(p->timestamp == q->timestamp)
						{
							k++;
							del = q;
							q = q->prev; 
							remove_node_interior(del);
						}
						q = q->next;
					}
				p = p->next;
			}
			
			printf("\n \n list with initial values: \n");
			print_list( &first0 );
			printf("\n \n deleteted elements : \n");
			print_list( &first2 );
			printf("\n \n elementele citite care se incadreaza in parametrii sunt:\n");
			print_list( &first1 );
					
			free_list(&first2, &last2);		
		}
		
		else if (option == 2)
		{
   			node* p = first1;
   			while(p->next != NULL)
   			{
   				if ( (p->next->timestamp - p->timestamp) >= 1 )
				   {
						p->next->timestamp = (p->timestamp + p->next->timestamp) / 2;   	
				   		p->next->data = (p->data + p->next->data) / 2;
				   }
				p = p->next;	
			}
			printf("\n \n otimizare a date in functie de timp: \n");
			print_list (&first1 );
		}
		
		else if(option == 3)
		{
   			printf("\n");
			printf("elementele citite care se incadreaza in parametrii sunt:\n");
			print_list( &first1 );
		}
		
		else if (option==4)//alt input initial
		{
			free_list(&first0, &last0);
			free_list(&first1, &last1);
			free_list(&first2, &last2);
			
			printf("please enter number of inputs: ");
			scanf("%d", &n);
			for(t=0; t<=n-1; t++)
			{		
				printf("\n please enter input no %d ( value timestamp ): ", t+1);
				scanf("%lf %lf", &data, &timestamp);
				add(&first0, &last0, data, timestamp);
			}
			copy_list( &first0, &last0, &first1, &last1);
		}
		
		printf("\n to do another operation press 1, otherwise press 0 : ");
		scanf("%d", &continuation);
		if (continuation == 1)
		{
			
			int input;
			printf("\n work further with the initial input (press 1) or the last op result (default insert any number): ");
			scanf("%d", &input);
			if (input == 1)
			{
				free_list(&first1, &last1);
				copy_list(&first0, &last0, &first1, &last1);
			}
			show_options();
			scanf("%d", &option);
		}

	}while (continuation == 1);
			
	free_list(&first0, &last0);
	free_list(&first1, &last1);
//	free_list(&first2, &last2);
	
	printf("\n \n Thank you for using my program <3");	
	sleep(2);		
}
