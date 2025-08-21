/**
 * @file otto_emoji_gif_utils.c
 * @brief Otto机器人GIF表情资源组件辅助函数实现
 */

#include <string.h>

#include "baidu_emoji_gif.h"

// 表情映射表
typedef struct {
    const char* name;
    const lv_image_dsc_t* gif;
} emotion_map_t;

// 外部声明的GIF资源
extern const lv_image_dsc_t angry;
extern const lv_image_dsc_t confident;
extern const lv_image_dsc_t confused;
extern const lv_image_dsc_t crying;
extern const lv_image_dsc_t embarrassed;
extern const lv_image_dsc_t happy;
extern const lv_image_dsc_t kissy;
extern const lv_image_dsc_t laughing;
extern const lv_image_dsc_t loving;
extern const lv_image_dsc_t neutral;
extern const lv_image_dsc_t relaxed;
extern const lv_image_dsc_t sad;
extern const lv_image_dsc_t shocked;
extern const lv_image_dsc_t sleepy;
extern const lv_image_dsc_t thinking;
extern const lv_image_dsc_t winking;

// 表情映射表
static const emotion_map_t emotion_maps[] = {
    {"angry", &angry},
    {"confident", &confident},
    {"confused", &confused},
    {"crying", &crying},
    {"embarrassed", &embarrassed},
    {"happy", &happy},
    {"kissy", &kissy},
    {"laughing", &laughing},
    {"loving", &loving},
    {"neutral", &neutral},
    {"relaxed", &relaxed},
    {"sad", &sad},
    {"shocked", &shocked},
    {"sleepy", &sleepy},
    {"thinking", &thinking},
    {"winking", &winking},
    {NULL, NULL}  // 结束标记
};

const char* emoji_gif_get_version(void) {
    return "1.0.3";
}

int emoji_gif_get_count(void) {
    return 16;
}

const lv_image_dsc_t* emoji_gif_get_by_name(const char* name) {
    if (name == NULL) {
        return NULL;
    }

    for (int i = 0; emotion_maps[i].name != NULL; i++) {
        if (strcmp(emotion_maps[i].name, name) == 0) {
            return emotion_maps[i].gif;
        }
    }

    return NULL;  // 未找到
}