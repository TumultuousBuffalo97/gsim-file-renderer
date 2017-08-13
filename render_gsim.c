#include <stdio.h>
#include <pthread.h>
#include "inc/structs.c"
#include "inc/global_vars.c"
#include "inc/png.c"
#include "inc/gfx.c"
#include "inc/readconf.c"
int main(int argc, char *argv[]) {
	int f,t,p;
	readsettings("render.conf");
	FILE *fp=fopen(infile,"r");
	fread(&numframes,sizeof(int),1,fp);
	fread(&framewidth,sizeof(int),1,fp);
	fread(&frameheight,sizeof(int),1,fp);
	fread(&nparts,sizeof(int),1,fp);
	printf("INFO: frames: %d, width: %d, height: %d\n",numframes,framewidth,frameheight);
	poss=calloc(numimagethreads,sizeof(struct scalar *));
	for(p=0;p<numimagethreads;++p) {
		poss[p]=calloc(nparts,sizeof(struct scalar));
	}
	gfx_init();
	for(f=0;f<numframes;f+=numimagethreads) {
		for(t=0;t<numimagethreads;++t) {
			for(p=0;p<nparts;++p) {
				fread(&poss[t][p].xp,sizeof(float),1,fp);
				fread(&poss[t][p].yp,sizeof(float),1,fp);
			}
		}
		for(t=0;t<numimagethreads;++t) {
			gfx_dftws[t].positions=&poss[t][0];
			gfx_dftws[t].buffer=frames[t];
			gfx_dftws[t].framenumber=f+t;
		}
		for(t=1;t<numimagethreads;++t) {
			pthread_create(&imagethreads[t],NULL,(void *)gfx_drawframe,&gfx_dftws[t]);
		}
		gfx_drawframe(&gfx_dftws[0]);
		for(t=1;t<numimagethreads;++t) {
			pthread_join(imagethreads[t],NULL);
		}
		printf("%d/%d\n",f,numframes);
	}
	fclose(fp);
	return 0;
}
