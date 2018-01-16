#ifndef _LOG_H_
#define _LOG_H_


#ifdef __cplusplus
extern "C" {
#endif

    void LOG_I(char *text);
    void LOG_W(char *text);
    void LOG_E(char *text);
    void LOG(char *text);


#ifdef __cplusplus
}
#endif


#endif
