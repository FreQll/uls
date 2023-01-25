#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1)
	{
		uls(".", 0, 0);
	}
	/*else if (argc == 2)
	{*/
		check_no_dir(argv);
		//add_cat(argv);
		
		check_dir(argv);
		


		//CREATIVE
		/*
		if (argv[1][0] == '-')
		{

			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			uls(".",op_a,op_l);
			
		}*/
	
	//}
	return 0;
}
