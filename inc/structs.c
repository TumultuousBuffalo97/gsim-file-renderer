struct scalar {
	float xp,yp;
};
struct RGBpixel {//for png
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
struct gfx_dfw {
	struct scalar *positions;
	struct RGBpixel *buffer;
	int framenumber;
};
