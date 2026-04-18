#ifndef texture_header
#define texture_header

struct TextureItem;

typedef struct {
	void (*bind)(struct TextureItem* tx);
	void (*unbind)(struct TextureItem* tx);
	void (*destroy)(struct TextureItem* tx);
} TextureItemInterface;	

typedef struct TextureItem {
	unsigned int id;
	const TextureItemInterface* ops;
} TextureItem;

void textureItem_init(TextureItem* tx, const char* path);

#endif
