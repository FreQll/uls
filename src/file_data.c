#include "../inc/uls.h"

void print_permission(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    // if(stat(argv[1], &fileStat) < 0)    
    //     return 1;

    //printf("Information for %s\n", name);
    // printf("---------------------------\n");
    // printf("File Size: \t\t%ld bytes\n", fileStat.st_size);
    // printf("Number of Links: \t%ld\n", fileStat.st_nlink);
    // printf("File inode: \t\t%ld\n", fileStat.st_ino);

    //printf("File Permissions: \t");

    if (S_ISDIR(fileStat.st_mode)) { //1
        mx_printstr("d");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IRUSR) { //2
        mx_printstr("r");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IWUSR) { //3
        mx_printstr("w");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IXUSR) { //4
        mx_printstr("x");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IRGRP) { //5
        mx_printstr("r");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IWGRP) { //5
        mx_printstr("w");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IXGRP) { //6
        mx_printstr("x");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IROTH) { //7
        mx_printstr("r");
    }
    else mx_printstr("-");
    
    if (fileStat.st_mode & S_IWOTH) { //8
        mx_printstr("w");
    }
    else mx_printstr("-");

    if (fileStat.st_mode & S_IXOTH) { //9
        mx_printstr("x");
    }
    else mx_printstr("-");

    // printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
}

void print_linked_links(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    mx_printint(fileStat.st_nlink);
}

void print_owners(char *name) {
    struct stat fileStat;
    stat(name, &fileStat);  // Error check omitted
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group  *gr = getgrgid(fileStat.st_gid);

    mx_printstr(pw->pw_name);
    mx_printstr(" ");
    mx_printstr(gr->gr_name);
}

void print_file_size(char *name, int spaces) {
    int size = get_file_size(name);

    if (get_num_digits(size) < spaces) {
        for (int i = 0; i < spaces - get_num_digits(size); i++) {
            mx_printchar(' ');
        }
    }
    
    mx_printint(size);
}

int get_file_size(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    int size = fileStat.st_size;

    return size;
}

void print_blocks(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    mx_printint(fileStat.st_blocks);
    mx_printstr("\n");
}

int get_blocks(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    return fileStat.st_blocks;
}

void print_file_time(char *name) {
    struct stat fileStat;
	stat(name, &fileStat);
    mx_printstr(convert_time(fileStat.st_mtime));
    //mx_printint(localtime(&(fileStat.st_ctime)));
}

char *convert_time(time_t t) {
    char * result;
	time_t curtime = time(NULL);
	char * time_str = ctime(&t);
   	time_str[mx_strlen(time_str)-1] = '\0';
   	char ** parts = mx_strsplit(time_str, ' ');
	parts[3][5] = '\0'; // delete seconds from time
	
	result = mx_strnew(12);
	result = mx_strcat(result, parts[1]);
	if (mx_strlen(parts[2]) == 2)
		result = mx_strcat(mx_strcat(result, " "), parts[2]);// DAY < 10
	else
		result = mx_strcat(mx_strcat(result, "  "), parts[2]); // DAY > 10
	
	if (curtime - t > 6*2629743) // format MON DAY YEAR
	{
		result = mx_strcat(mx_strcat(result, "  "), parts[4]);
	}
	else // format MON DAY TIME
	{
		result = mx_strcat(mx_strcat(result, " "), parts[3]);
	}
	mx_del_strarr(&parts);
	//free(time_str);
	return result;
}
