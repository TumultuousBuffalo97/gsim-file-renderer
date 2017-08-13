void putRect(struct RGBpixel *buffer,int x, int y, int pwidth, int pheight) {
	int xor=x,yor=y;
	for(x=xor+1;x<xor+pwidth;++x) {
		if(!(x>framewidth||yor>frameheight||x<0||yor<0)) {
			writeRGBpixel(&buffer[x+yor*framewidth],255,255,255);
		}
		if(!(x>framewidth||(yor+pheight>frameheight)||x<0||yor<0)) {
			writeRGBpixel(&buffer[x+((yor+pheight)*framewidth)],255,255,255);
		}
	}
	for(y=yor+1;y<yor+pheight;++y) {
		if(!(xor>framewidth||y>frameheight||xor<0||y<0)) {
			writeRGBpixel(&buffer[xor+(y*framewidth)],255,255,255);
		}
		if(!(xor>framewidth||y>frameheight||xor<0||y<0)) {
			writeRGBpixel(&buffer[(xor+pwidth)+(y*framewidth)],255,255,255);
		}
	}
}
void *gfx_drawframe(struct gfx_dfw *wrapper) {
	static __thread int i;
	static __thread char filepath[256]={0};
	memset(wrapper->buffer,0,framewidth*frameheight*sizeof(struct RGBpixel));
	for(i=0;i<nparts;++i) {
		putRect(wrapper->buffer,wrapper->positions[i].xp,wrapper->positions[i].yp,3,3);
	}
	sprintf(filepath,"./%s/%06d.png",outdir,wrapper->framenumber);
	writePNGimage(filepath,NULL,wrapper->buffer,framewidth,frameheight);
	return 0;
}
void gfx_init() {
	int i;
	frames=calloc(numimagethreads,sizeof(struct RGBpixel *));
	imagethreads=calloc(numimagethreads,sizeof(pthread_t));
	gfx_dftws=calloc(numimagethreads,sizeof(struct gfx_dfw));
	for(i=0;i<numimagethreads;++i) {
		frames[i]=calloc(framewidth*frameheight,sizeof(struct RGBpixel));
	}
}
