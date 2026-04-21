#ifndef texture_header
#define texture_header

struct TextureItem;

typedef struct {
	int (*bind)(struct TextureItem* tx, int unit);
	void (*unbind)(struct TextureItem* tx, int unit);
	void (*destroy)(struct TextureItem* tx);
} TextureItemInterface;	

typedef struct TextureItem {
	unsigned int id;
	const TextureItemInterface* ops;
} TextureItem;

void textureItem_init(TextureItem* tx, const char* path);

#endif
