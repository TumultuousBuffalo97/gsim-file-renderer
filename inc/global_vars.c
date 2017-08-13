char outdir[256]="./images/";
char infile[256]="out.gsim";
int numframes;
int framewidth;
int frameheight;
int numimagethreads;

int nparts;
pthread_t *imagethreads;
struct gfx_dfw *gfx_dftws;
struct RGBpixel **frames;
struct scalar **poss;
