#include <string.h>
char *readvar(char *settings, char *varname) {
	char *varstart;
	char *varend;
	char *var;
	varstart=strstr(settings,varname)+strlen(varname)+1;
	varend=strstr(varstart,"\n");
	var=calloc(varend-varstart,sizeof(char));
	strncpy(var,varstart,varend-varstart);
	return var;
}
void readsettings(char *path) {
	int length;
	char *settings;
	//open the file
	FILE *fp=fopen(path,"r");
	if(fp==NULL) {
		printf("ERROR: cannot find the settings file");
		return ;
	}
	//go to the end of the file
	fseek(fp,0,SEEK_END);
	//get the length of the file
	length=ftell(fp);
	//go to the beggining of the file
	fseek(fp,0,SEEK_SET);
	//allocate memory to put the file contents
	settings=calloc(length,sizeof(char));
	//read the file contents into the buffer
	fread(settings,sizeof(char),length,fp);
	//read the variables
	//fps=atoi(readvar(settings,"fps"));
	//viewport
	//performance
	numimagethreads=atoi(readvar(settings,"imagethreads"));
}
