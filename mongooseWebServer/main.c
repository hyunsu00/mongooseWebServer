// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "mongoose.h"

const char *s_listening_url = "http://0.0.0.0:8000";

// HTTP request handler function
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_serve_opts opts = {
			.root_dir = "/public",
			.fs = &mg_fs_packed
		};
		mg_http_serve_dir(c, ev_data, &opts);
	}
	(void)fn_data;
}

int main()
{
	struct mg_mgr mgr;
	mg_log_set(MG_LL_INFO);
	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, s_listening_url, fn, NULL);
	while (true) mg_mgr_poll(&mgr, 500);
	mg_mgr_free(&mgr);
	return 0;
}
