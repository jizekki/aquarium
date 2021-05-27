#ifndef CONFIG_H
#define CONFIG_H

void config__init()__attribute__((constructor));
int config__get_port();
int config__get_timeout();
int config__get_fish_interval();

#endif //CONFIG_H
