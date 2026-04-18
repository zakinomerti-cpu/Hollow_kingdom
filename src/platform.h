#ifndef platformCLASS_H
#define platformCLASS_H

typedef struct platform {
	void (*platformInit)(struct platform*);
	void (*render)(struct platform*);
	void (*setStartFunc)(struct platform*, void (*)(void));
	void (*setDisplayFunc)(struct platform*, void (*)(void));
	unsigned char (*shouldClose)(struct platform*);
	
	void (*getMousePos)(struct platform*, int* mx, int* my);
	unsigned char (*click)(struct platform*);

	void (*getPressedKeys)(struct platform*, unsigned char (*keys)[256]);


	void (*shutDown)(struct platform*);
	void (*setShutDownFunc)(struct platform*, void(*)(void));
	void (*createWindow)(struct platform*, const char*, int, int);

	//private
	void(*startFunc)(void);

} platform;

void glutPlatform_init(platform*, int, char**);

#endif