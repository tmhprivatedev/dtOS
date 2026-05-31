#include <stdint.h>
#include <stddef.h>
#include "include/limine.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0	
};

__attribute__((used, section(".limine_reqs")))
static volatile void *limine_requests_array[] = {
	(void *)&limine_base_revision,
	(void *)&framebuffer_request,	
};

void put_pixel(struct limine_framebuffer *fb, uint64_t x, uint64_t y, uint32_t color) {
	uint32_t *fb_ptr = (uint32_t *)fb->address;
	size_t index = y * (fb->pitch / 4) * x;
	fb_ptr[index] = color;
}

void kernel_main(void) {

	if (LIMINE_BASE_REVISION_SUPPORTED == 0) {
		for (;;) {__asm__ volatile("hlt"); }
	}

	if (framebuffer_request.response == NULL) {
		for (;;) { __asm__ volatile("hlt"); }
	}

	struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];

	for (uint64_t y = 0; y < fb->height; y++) {
		for (uint64_t x=0; x < fb->width; x++) {
			put_pixel(fb, x, y, 0x1e1e2e);
		}
	}

	for (;;) {
		__asm__ volatile("cli; hlt");
	}

}
