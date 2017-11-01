#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	unsigned long int neuron1;
	unsigned long int neuron2;
	unsigned long int wheight;
}link;

typedef struct
{
	int layer;
	int value;
}neurons;

void print_to_file(link *brain, int size, char *file)
{
	int i = 0;
	FILE *fp;

	fp = fopen(file, "wb");

	fwrite(brain, sizeof(link), size, fp);

	fclose(fp);
}

void read_from_file(link *brain, char *file)
{
	FILE *fp;
	int i=0;

	fp = fopen(file, "rb");

	fread(brain, sizeof(link), size, fp);

	fclose(fp);
}

link* create_vec(int size)
{
	link *brain;

	brain = (link*)malloc(size*sizeof(link));
	if(brain == NULL)
	{
		printf("Error allocating memory!!!\n");
	}
	return brain;
}


void hyperbola_param(int max_x, int max_y, int t_max_x, double *a, double *b, double *c)
{
	//the parabola has an equation of c/(x+a)-b
	//it might no work for numbers above 1000 for max_x
	//standard values are max_x = 70, max_y = 100, t_max_x = 10
	double aa, ba, ca, caux;

	ca=1;
	double c_av;

	do
	{
		caux = ca;
		ca *= 2;
		aa = ((-max_x*max_y + sqrt(max_x*max_y*max_x*max_y + 4*max_x*max_y*ca))/(2*max_y));
		ba = ca/(max_x + aa);
	}while(ca/(0.2*max_x+aa)-ba < t_max_x);

	while(ca - caux >= 0.01)
	{
		c_av = (caux+ca)/2;
		aa = ((-max_x*max_y + sqrt(max_x*max_y*max_x*max_y + 4*max_x*max_y*c_av))/(2*max_y));
		ba = c_av/(max_x + aa);
		if(c_av/(0.2*max_x+aa)-ba < t_max_x)
		{
			caux = c_av;
		}
		else
		{
			ca = c_av;
		}
	}

	*a = aa; *b = ba; *c = ca;
}

double get_hyperbola_val(double a, double b, double c, double x)
{
	return c/(x+a)-b;
}

/**********************************************************************************************
Function: insert_connection

Ojective: insert a connection inside the brain. This function works recursively, it adds a
	connection in the last position of a cerain layer and does the same for the substituted
	connection until it reaches the end.
	1_1_2_2_2_2_3_3_3_4_4_5_6_6 and i wanted to insert a 2, it would work like this:
	1_1_2_2_2_2_2n_3_3_4_4_5_6_6
	1_1_2_2_2_2_2n_3_3_3m_4_5_6_6
	1_1_2_2_2_2_2n_3_3_3m_4_4m_6_6
	1_1_2_2_2_2_2n_3_3_3m_4_4m_5m_6
	1_1_2_2_2_2_2n_3_3_3m_4_4m_5m_6_6m

	where n stands for new and m for moved

Arguments:

Return value:
	
**********************************************************************************************/
void insert_connection(link *brain, neurons *n, unsigned long int neuron1, unsigned long int neuron2, unsigned long int start, unsigned long int brain_size, unsigned long int layers_size)
{
	unsigned long int aux1 = start, aux2 = brain_size;
	unsigned long int av = (aux1+aux2)/2;

	while(aux2 - aux1 != 1)
	{
		if(brain[av].layer <= n[neuron1].layer && brain[av].layer != 0)
		{
			aux1 = av;
			av = (aux1+aux2)/2;
		}
		else
		{
			aux2 = av;
			av = (aux1+aux2)/2;
		}
	}
	if(brain[aux2].layer != 0)
	{
		insert_connection(brain, n, brain[aux2].neuron1, brain[aux2].neuron2, aux1, brain_size, layers_size);
	}

	brain[aux2].neuron1 = neuron1;
	brain[aux2].neuron2 = neuron2;
	brain[aux2].layer = layers[neuron1];
}


//still missing functions
void mutate_add_connection(link *brain, neurons *n, unsigned long int neuron1, unsigned long int neuron2, unsigned long int brain_size, unsigned long int layers_size)
{
	if(layers[neuron1] > layers[neuron2])
	{
		insert_connection(brain, n, neuron2, neuron1, 0, brain_size, layers_size);
	}
	else if(layers[neuron1] < layers[neuron2])
	{
		insert_connection(brain, n, neuron1, neuron2, 0, brain_size, layers_size);
	}
	else
	{
		if(rand%2 == 0)
		{
			n[neuron1].layer++;
			increment_layers_above();
			insert_connection();
		}
		else
		{
			n[neuron2].layer++;
			increment_layers_above();
			insert_connection();
		}
	}
}

//still missing functions
void mutate_add_neuron(link *brain, neurons *n, unsigned long int connection, unsigned long int brain_size, unsigned long int layers_size)
{
	unsigned long int neuron1, neuron2;

	remove_connection();
	insert_connection();
	insert_connection();
}

void mutate_connection(link *brain, unsigned long int connection)
{
	double x;
	static double a, b, c;
	static int init=1;

	if(init == 1)
	{
		hyperbola_param(100, 70, 10, &a, &b, &c);
		init = 0;
	}

	x = get_hyperbola_val(a, b, c, (rand()%100000)/100000);

	if(rand()%2 == 0)
	{
		brain[connection].wheight *= 1 + get_hyperbola_val(a, b, c, rand()%)/100;
	}
	else
	{
		brain[connection].wheight *= 1 - get_hyperbola_val(a, b, c, rand()%)/100;
	}
}

void mutate()
{
	
}

