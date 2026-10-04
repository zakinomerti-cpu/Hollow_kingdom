#ifndef platformCLASS_H
#define platformCLASS_H

typedef struct platform platform;

typedef struct platformInterface {
	void (*platformInit)(struct platform*);
	void (*render)(struct platform*);
	void (*setStartFunc)(struct platform*, void (*)(void));
	void (*setDisplayFunc)(struct platform*, void (*)(void));
	unsigned char (*shouldClose)(struct platform*);
} platformInterface;

struct platform {
	char* title;
	int width;
	int height;
	const platformInterface* ops;
};

void platform_init(platform* plt, const char*, int, int);

#endif