#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <Winspool.h>
#endif

/********************* definice konstant *******************************/

#define TEST FALSE


#define CONF_WINDOW_TITLE "Pokladní systém"
#define CONF_COMPANY_ICON_PATH "img/logo-mlyn-dubecko.png"
#define CONF_CYCLIC_INTERUPT_INTERVAL 1000

enum _side_orientation_
{
	x_axis = 0,
	y_axis
};

enum _lang_index_description_
{
	lang_cz = 0,

	lang_num	
};

enum _order_list_columns_
{
	GOODS_COLUMN = 0,
	QUANTITY_COLUMN,
	PRICE_WITHOUT_TAX_COLUMN,
	PRICE_WITH_TAX_COLUMN,

	N_COLUMNS
};

/******************** deklarace struktur *******************************/

struct _controler_;
typedef struct _controler_ controler;

struct _user_management_;
typedef struct _user_management_ user_management;

struct _eet_;
typedef struct _eet_ eet;

struct _settings_;
typedef struct _settings_ settings;

struct _printer_;
typedef struct _printer_ printer;

struct _alarm_buffer_;
typedef struct _alarm_buffer_ alarm_buffer;

struct _database_;
typedef struct _database_ database;

struct _order_list_;
typedef struct _order_list_ order_list;

struct _order_service_;
typedef struct _order_service_ order_service;

struct _hand_scanner_;
typedef struct _hand_scanner_ hand_scanner;

struct _order_item_;
typedef struct _order_item_ order_item;




struct _view_;
typedef struct _view_ view;

struct _view_base_;
typedef struct _view_base_ view_base;

struct _view_base_screen_;
typedef struct _view_base_screen_ view_base_screen;

struct _multi_lang_;
typedef struct _multi_lang_ multi_lang;

struct _lang_;
typedef struct _lang_ lang;

struct _view_bill_viewer_screen_;
typedef struct _view_bill_viewer_screen_ view_bill_viewer_screen;

struct _view_order_screen_;
typedef struct _view_order_screen_ view_order_screen;

struct _view_manual_input_screen_;
typedef struct _view_manual_input_screen_ view_manual_input_screen;

struct _view_settings_screen_;
typedef struct _view_settings_screen_ view_settings_screen;

struct _view_order_finish_screen_;
typedef struct _view_order_finish_screen_ view_order_finish_screen;

struct _alarm_widget_;
typedef struct _alarm_widget_ alarm_widget;

struct _value_widget_;
typedef struct _value_widget_ value_widget;

struct _order_list_widget_;
typedef struct _order_list_widget_ order_list_widget;


struct _geometry_;
typedef struct _geometry_ geometry;


/****************** definice struktur *********************************/


struct _geometry_
{
	uint32_t width;
	uint32_t height;
};


struct _controler_
{
	eet * eet_ref;
	printer * printer_ref;
	order_list * order_list_ref;
	database * database_ref;
	settings * settings_ref;
	user_management * user_management_ref;

	alarm_buffer * alarm_buffer_ref;
};

struct _user_management_
{

};

struct _eet_
{

};

struct _settings_
{

};

struct _printer_
{

};

struct _alarm_buffer_
{
	bool error;
	bool warning;


};

struct _database_
{

};

struct _order_list_
{
	order_service * order_service_ref;

};

struct _order_service_
{
	hand_scanner * hand_scanner_ref;
};

struct _hand_scanner_
{

};

struct _order_item_
{

};




struct _view_
{
	GtkWidget * window;
	GtkWidget * container;
	GtkWidget * company_icon;

	controler * controler_ref;
	view_base * view_base_ref;

	view_bill_viewer_screen * view_bill_viewer_screen_ref;
	view_order_screen * view_order_screen_ref;
	view_manual_input_screen * view_manual_input_screen_ref;
	view_settings_screen * view_settings_screen_ref;
	view_order_finish_screen * view_order_finish_screen_ref;

	alarm_widget * alarm_widget_ref;
};

struct _view_base_
{
	controler * controler_ref;

	GtkWidget * stack_container;

	multi_lang * multi_lang_ref;

	geometry window_base_geometry;
	geometry window_geometry;
	geometry screen_geometry;

	double window_width_ratio;
	double window_height_ratio;
};

struct _view_base_screen_
{
	GtkWidget * container;
	view_base * view_base_ref;
};


struct _multi_lang_
{
	uint8_t language_index;

	lang ** lang_struct;
};


struct _lang_
{
	const char * language_name;

	const char * default_sum_price_text;
	const char * currency_text;
	const char * btn_back_text;


	const char * btn_clear_order_text;
	const char * btn_increase_quantity_text;
	const char * btn_decrease_quantity_text;
	const char * btn_pay_text;
	const char * btn_manual_input_text;
	const char * lbl_sum_text;
	const char * order_list_widget_goods_text;
	const char * order_list_widget_quantity_text;
	const char * order_list_widget_price_without_tax_text;
	const char * order_list_widget_price_with_tax_text;

	const char * btn_prev_text;
	const char * btn_next_text;

	const char * btn_print_bill_text;
	const char * btn_finish_text;

	const char * lbl_customer_payed_text;
	const char * lbl_order_sum_text;
	const char * lbl_money_back_text;
};

struct _view_bill_viewer_screen_
{
	view_base_screen * base_screen_ref;
};

struct _view_order_screen_
{
	view_base_screen * base_screen_ref;

	GtkWidget * list;
	GtkWidget * scroll;

	GtkWidget * btn_clear_order;
	GtkWidget * btn_increase_quantity;
	GtkWidget * btn_decrease_quantity;
	GtkWidget * btn_pay;
	GtkWidget * btn_manual_input;

	GtkWidget * lbl_order_sum;
	GtkWidget * lbl_sum_price;
};

struct _view_manual_input_screen_
{
	view_base_screen * base_screen_ref;
	GtkWidget *** button_matrix;

	GtkWidget * btn_next;
	GtkWidget * btn_prev;
	GtkWidget * btn_back;
};

struct _view_settings_screen_
{
	view_base_screen * base_screen_ref;

};

struct _view_order_finish_screen_
{
	view_base_screen * base_screen_ref;
	
	GtkWidget *** button_matrix;

	GtkWidget * btn_print_bill;
	GtkWidget * btn_back;
	GtkWidget * btn_finish;
	
	value_widget * order_sum_price;
	value_widget * customer_payed;
	value_widget * count_money_back;
};

struct _alarm_widget_
{
	GtkWidget * draw_area;

	alarm_buffer * alarm_buffer_ref;

	geometry widget_geometry;

	bool blink;
};



struct _value_widget_
{
	geometry widget_geometry;

	const char * label;
	char * value;

	uint32_t font_size;
	const char * font_family;
	
	double bg_color[3];
	double fg_color[3];

	uint32_t left_padding;
	uint32_t right_padding;

	GtkWidget * draw_area;
};


struct _order_list_widget_
{
	geometry widget_geometry;

	char ** column_title_list;
	uint8_t column_title_size;

	const char * font_family;
	uint32_t font_size;

	order_list * source_order_list;
	
	GtkWidget * draw_area;

	bool is_row_selected;
	uint32_t selected_row_index;

	uint8_t visible_row_number;
};


/***************** deklarace funkcí **********************************/

controler * controler_new();
void controler_build_sub_modules(controler * this);
void controler_finalize(controler * this);

user_management * user_management_new();
void user_management_finalize(user_management * this);

eet * eet_new();
void eet_finalize(eet * this);

settings * settings_new();
void settings_finalize(settings * this);

printer * printer_new();
void printer_finalize(printer * this);

alarm_buffer * alarm_buffer_new();
void alarm_buffer_reset_error(alarm_buffer * this);
void alarm_buffer_finalize(alarm_buffer * this);

database * database_new();
void database_finalize(database * this);

order_list * order_list_new();
void order_list_finalize(order_list * this);

order_service * order_service_new();
void order_service_finalize(order_service * this);

hand_scanner * hand_scanner_new();
void hand_scanner_finalize(hand_scanner * this);

order_item * order_item_new();
void order_item_finalize(order_item * this);

view * view_new(controler * controler_ref);
gboolean view_cyclic_interupt(gpointer param);
bool view_load_company_icon(view * this);
GtkWidget * view_initialize_company_icon_widget(GdkPixbuf * icon, double window_width_ratio);
void view_pack_container(view * this);
void view_hide_cursor(view * this);
void view_initialize(view * this);
void view_build_main_window(view * this);
void view_build_screens(view * this);
void view_build_alarm_widget(view * this);
void view_pack_screens(view * this);
void view_initialize_base_class(view * this);
void view_signals(view * this);
void view_finalize(view * this);
void view_window_exit_callback(GtkWidget * widget, gpointer param);
void view_close_callback(GtkWidget * widget, GdkEventButton * event, gpointer * param);

view_base * view_base_new(controler * controler_ref, geometry window_base_geomtry);
void view_base_build_container(view_base * this);
void view_base_set_current_window_geometry(view_base * this, geometry window_geometry);
void view_base_read_current_screen_geometry(view_base * this);
void view_base_show_order_screen(view_base * this);
void view_base_show_settings_screen(view_base * this);
void view_base_show_order_finish_screen(view_base * this);
void view_base_show_bill_viewer_screen(view_base * this);
void view_base_show_manual_input_screen(view_base * this);
void view_base_count_ratio(view_base * this);
double view_base_recount_x_geometry_by_ratio(view_base * this, uint32_t base_position);
double view_base_recount_y_geometry_by_ratio(view_base * this, uint32_t base_position);
GdkPixbuf * view_base_load_image(char * image_address);
GdkPixbuf * view_base_scale_icon(GdkPixbuf * icon, enum _side_orientation_ axis, double new_size);
void view_base_finalize(view_base * this);

view_base_screen * view_base_screen_new(view_base * view_base_ref);
GtkWidget * view_base_screen_build_button(view_base_screen * this, double width, double height);
GtkWidget * view_base_screen_build_label(view_base_screen * this, double width, double height, float xalign);
void view_base_screen_set_label_markup_text(GtkWidget * label, const char * string, int font_size);
void view_base_screen_finalize(view_base_screen * this);

multi_lang * multi_lang_new();
lang * multi_lang_get_current_language(multi_lang * this);
void multi_lang_initialize_language_structure(multi_lang * this);
void multi_lang_initialize_czech_text(multi_lang * this);
void multi_lang_set_alarm_text_czech(lang * this);
void multi_lang_set_order_screen_text_czech(lang * this);
void multi_lang_set_manual_input_screen_text_czech(lang * this);
void multi_lang_set_order_finish_screen_text_czech(lang * this);
void multi_lang_set_settings_screen_text_czech(lang * this);
void multi_lang_set_bill_viewer_screen_text_czech(lang * this);
void multi_lang_finalize(multi_lang * this);

view_bill_viewer_screen * view_bill_viewer_screen_new(view_base * view_base_ref);
void view_bill_viewer_screen_build_widgets(view_bill_viewer_screen * this);
void view_bill_viewer_screen_language(view_bill_viewer_screen * this);
void view_bill_viewer_screen_pack_widgets(view_bill_viewer_screen * this);
void view_bill_viewer_screen_signals(view_bill_viewer_screen * this);
void view_bill_viewer_screen_finalize(view_bill_viewer_screen * this);

view_order_screen * view_order_screen_new(view_base * view_base_ref);
void view_order_screen_build_widgets(view_order_screen * this);
GtkTreeViewColumn * view_order_screen_add_header_column(uint32_t position, const char * title);
void view_order_screen_build_list_widget(view_order_screen * this);
void view_order_screen_language(view_order_screen * this);
void view_order_screen_pack_widgets(view_order_screen * this);
void view_order_screen_signals(view_order_screen * this);
void view_order_screen_btn_manual_input_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_increase_quantity_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_decrease_quantity_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_pay_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_clear_order_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_finalize(view_order_screen * this);

view_manual_input_screen * view_manual_input_screen_new(view_base * view_base_ref);
void view_manual_input_screen_build_widgets(view_manual_input_screen * this);
void view_manual_input_screen_language(view_manual_input_screen * this);
void view_manual_input_screen_pack_widgets(view_manual_input_screen * this);
void view_manual_input_screen_signals(view_manual_input_screen * this);
void view_manual_input_screen_btn_prev_click_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_btn_back_click_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_btn_next_click_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_0x0_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_0x1_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_0x2_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_0x3_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_0x4_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_1x0_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_1x1_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_1x2_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_1x3_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_1x4_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_2x0_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_2x1_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_2x2_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_2x3_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_button_metrix_2x4_clicked_callback(GtkWidget * widget, gpointer param);
void view_manual_input_screen_finalize(view_manual_input_screen * this);

view_settings_screen * view_settings_screen_new(view_base * view_base_ref);
void view_settings_screen_build_widgets(view_settings_screen * this);
void view_settings_screen_language(view_settings_screen * this);
void view_settings_screen_pack_widgets(view_settings_screen * this);
void view_settings_screen_signals(view_settings_screen * this);
void view_settings_screen_finalize(view_settings_screen * this);

view_order_finish_screen * view_order_finish_screen_new(view_base * view_base_ref);
void view_order_finish_screen_build_widgets(view_order_finish_screen * this);
void view_order_finish_screen_pack_widgets(view_order_finish_screen * this);
void view_order_finish_screen_language(view_order_finish_screen * this);
void view_order_finish_screen_signals(view_order_finish_screen * this);
void view_order_finish_screen_btn_print_bill_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_btn_back_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_btn_finish_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_0x0_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_0x1_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_0x2_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_1x0_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_1x1_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_1x2_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_2x0_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_2x1_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_2x2_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_3x0_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_3x1_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_button_matrix_3x2_click_callback(GtkWidget * widget, gpointer param);
void view_order_finish_screen_finalize(view_order_finish_screen * this);

alarm_widget * alarm_widget_new(alarm_buffer * alarm_buffer_ref, geometry widget_geometry);
gboolean alarm_widget_draw_callback(GtkWidget * drawing_area, cairo_t * cr, gpointer param);
void alarm_widget_reset_error_buffer_callback(GtkWidget * widget, GdkEventButton * event, gpointer param);
void alarm_widget_build(alarm_widget * this);
void alarm_widget_signals(alarm_widget * this);
void alarm_widget_finalize(alarm_widget * this);

value_widget * value_widget_new(geometry widget_geometry);
void value_widget_set_geometry(value_widget * this, geometry widget_geometry);
geometry value_widget_get_geometry(value_widget * this);
double * value_widget_get_forground_color(value_widget * this);
double * value_widget_get_background_color(value_widget * this);
void value_widet_set_foreground_color(value_widget * this, double fg_color[3]);
void value_widget_set_background_color(value_widget * this, double bg_color[3]);
void  value_widget_set_value(value_widget * this, char * value);
char * value_widget_get_value(value_widget * this);
void value_widget_set_label(value_widget * this, const char * label);
const char * value_widget_get_label(value_widget * this);
gboolean value_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param);
void value_widget_set_font_size(value_widget * this, uint32_t font_size);
uint32_t value_widget_get_font_size(value_widget * this);
void value_widget_set_font_family(value_widget * this, const char * font_family);
const char * value_widget_get_font_family(value_widget * this);
void value_widget_set_left_padding(value_widget * this, uint32_t left_padding);
void value_widget_set_right_padding(value_widget * this, uint32_t right_padding);
uint32_t value_widget_get_right_padding(value_widget * this);
uint32_t value_widget_get_left_padding(value_widget * this);
void value_widget_signals(value_widget * this);

order_list_widget * order_list_widget_new(geometry widget_geometry);
void order_list_widget_set_column_structure(order_list_widget * this, uint8_t columnt_title_size, const char ** column_title_list);
void order_list_widget_signals(order_list_widget * this);
void order_list_widget_set_source(order_list_widget * this, order_list * source_order_list);
void order_list_widget_repaint(order_list_widget * this);
uint32_t order_list_widget_get_selected_row(order_list_widget * this);
bool order_list_widget_is_selected(order_list_widget * this);
void order_list_widget_cancel_selection(order_list_widget * this);
gboolean order_list_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param);
gpointer order_list_widget_click_callback(GtkWidget * widget, GdkEvent * event, gpointer param);
gboolean order_list_widget_scroll_callback(GtkWidget * widget, GdkEvent * event, gpointer param);


/********************* definice funkcí *******************************/


/*********************** module controler *******************************/
controler * controler_new()
{
	controler * this = (controler*) malloc(sizeof(controler));

	controler_build_sub_modules(this);

	return this;
}


void controler_build_sub_modules(controler * this)
{
	this->eet_ref = eet_new();
	this->printer_ref = printer_new();
	this->order_list_ref = order_list_new();
	this->database_ref = database_new();
	this->settings_ref = settings_new();
	this->user_management_ref = user_management_new();

	this->alarm_buffer_ref = alarm_buffer_new();
}

void controler_finalize(controler * this)
{
	eet_finalize(this->eet_ref);
	printer_finalize(this->printer_ref);
	order_list_finalize(this->order_list_ref);
	database_finalize(this->database_ref);
	settings_finalize(this->settings_ref);
	user_management_finalize(this->user_management_ref);

	alarm_buffer_finalize(this->alarm_buffer_ref);

	free(this);
}

/**************************** modul user_management **********************/
user_management * user_management_new()
{
	user_management * this = (user_management*) malloc(sizeof(user_management));

	return this;
}

void user_management_finalize(user_management * this)
{
	free(this);
}



/************************** modul eet ************************************/
eet * eet_new()
{
	eet * this = (eet *) malloc(sizeof(eet));

	return this;
}

void eet_finalize(eet * this)
{
	free(this);
}


/************************* modul settings *******************************/
settings * settings_new()
{
	settings * this = (settings *) malloc(sizeof(settings));

	return this;
}

void settings_finalize(settings * this)
{
	free(this);
}


/************************ modul printer **********************************/
printer * printer_new()
{
	printer * this = (printer*) malloc(sizeof(printer));

	return this;
}

void printer_finalize(printer * this)
{
	free(this);
}


/************************** modul alarm_buffer **************************/
alarm_buffer * alarm_buffer_new()
{
	alarm_buffer * this = (alarm_buffer*) malloc(sizeof(alarm_buffer));
	
	this->error = true;
	this->warning = false;

	return this;
}


void alarm_buffer_reset_error(alarm_buffer * this)
{

}

void alarm_buffer_finalize(alarm_buffer * this)
{
	free(this);
}

/************************* modul database ********************************/
database * database_new()
{
	database * this = (database*) malloc(sizeof(database));

	return this;
}

void database_finalize(database * this)
{
	free(this);
}


/***************************** modul order_list ***************************/
order_list * order_list_new()
{
	order_list * this = (order_list*) malloc(sizeof(order_list));

	this->order_service_ref = order_service_new();

	return this;
}

void order_list_finalize(order_list * this)
{
	order_service_finalize(this->order_service_ref);

	free(this);
}


/***************************** modul order_service *************************/
order_service * order_service_new()
{
	order_service * this = (order_service*) malloc(sizeof(order_service));

	this->hand_scanner_ref = hand_scanner_new();

	return this;
}

void order_service_finalize(order_service * this)
{
	hand_scanner_finalize(this->hand_scanner_ref);

	free(this);
}


/***************************** modul hand_scanner **************************/
hand_scanner * hand_scanner_new()
{
	hand_scanner * this = (hand_scanner*) malloc(sizeof(hand_scanner));

	return this;
}

void hand_scanner_finalize(hand_scanner * this)
{
	free(this);
}


/*************************** modul order_item *******************************/
order_item * order_item_new()
{
	order_item * this = (order_item *) malloc(sizeof(order_item));

	return this;
}

void order_item_finalize(order_item * this)
{
	free(this);
}




/************************** modul base_view ******************************/

view_base * view_base_new(controler * controler_ref, geometry window_base_geometry)
{
	view_base * this = (view_base*) malloc(sizeof(view_base));

	this->controler_ref = controler_ref;

	this->window_base_geometry.width = window_base_geometry.width;
	this->window_base_geometry.height = window_base_geometry.height;

	view_base_read_current_screen_geometry(this);

	view_base_build_container(this);

	this->multi_lang_ref = multi_lang_new();

	return this;
}

void view_base_build_container(view_base * this)
{
	this->stack_container = gtk_stack_new();

	gtk_widget_set_size_request(GTK_WIDGET(this->stack_container), 
			this->screen_geometry.width, 
			view_base_recount_y_geometry_by_ratio(this, this->window_base_geometry.height-125));
}

void view_base_set_current_window_geometry(view_base * this, geometry window_geometry)
{
	this->window_geometry.width = window_geometry.width;
	this->window_geometry.height = window_geometry.height;
}

void view_base_show_order_screen(view_base * this)
{
	gtk_stack_set_visible_child_name(GTK_STACK(this->stack_container), "order_screen");
}

void view_base_show_settings_screen(view_base * this)
{
	gtk_stack_set_visible_child_name(GTK_STACK(this->stack_container), "settings_screen");
}

void view_base_show_order_finish_screen(view_base * this)
{
	gtk_stack_set_visible_child_name(GTK_STACK(this->stack_container), "order_finish_screen");
}

void view_base_show_bill_viewer_screen(view_base * this)
{
	gtk_stack_set_visible_child_name(GTK_STACK(this->stack_container), "bill_viewer_screen");
}

void view_base_show_manual_input_screen(view_base * this)
{
	gtk_stack_set_visible_child_name(GTK_STACK(this->stack_container), "manual_input_screen");
}

void view_base_read_current_screen_geometry(view_base * this)
{
	GdkRectangle system_geometry;

	GdkDisplay* display = gdk_display_get_default();
        GdkMonitor* monitor = gdk_display_get_monitor(display, 0);
        gdk_monitor_get_workarea(monitor, &system_geometry);

	this->screen_geometry.width = system_geometry.width;
	this->screen_geometry.height = system_geometry.height;

	view_base_count_ratio(this);
}

void view_base_screen_set_label_markup_text(GtkWidget * label, const char * string, int font_size)
{
	char label_text[128];

	sprintf(label_text, "<span font_desc=\"%d\"><b>%s</b></span>", font_size, string);
	gtk_label_set_markup(GTK_LABEL(label), label_text);
}

void view_base_count_ratio(view_base * this)
{
	this->window_width_ratio = ((double) this->screen_geometry.width) / ((double) this->window_base_geometry.width);
	this->window_height_ratio = ((double) this->screen_geometry.height) / ((double) this->window_base_geometry.height);
}

double view_base_recount_x_geometry_by_ratio(view_base * this, uint32_t base_position)
{
	return (this->window_width_ratio * ((double) base_position));
}

double view_base_recount_y_geometry_by_ratio(view_base * this, uint32_t base_position)
{
	return (this->window_height_ratio * ((double) base_position));
}

GdkPixbuf * view_base_load_image(char * image_address)
{
	GError * error = NULL;
	GdkPixbuf * image = gdk_pixbuf_new_from_file(image_address, &error);

	return image;
}

GdkPixbuf * view_base_scale_icon(GdkPixbuf * icon, enum _side_orientation_ axis, double new_size)
{
	GdkPixbuf* scaled_icon = NULL;

	if(icon != NULL)
	{
		if(axis == y_axis)
		{
			double ratio = ((double) new_size)/((double)gdk_pixbuf_get_height(icon));
			double scale = (ratio * ((double)gdk_pixbuf_get_width(icon)));
			scaled_icon = gdk_pixbuf_scale_simple (icon, (int) scale, new_size, GDK_INTERP_HYPER);
		}
		else
		{
			double ratio = ((double) new_size)/((double)gdk_pixbuf_get_width(icon));
			double scale = (ratio * ((double)gdk_pixbuf_get_height(icon)));
			scaled_icon = gdk_pixbuf_scale_simple (icon, (int) new_size, scale, GDK_INTERP_HYPER);
		}
	}

	return scaled_icon;
}


void view_base_finalize(view_base * this)
{
	controler_finalize(this->controler_ref);
	multi_lang_finalize(this->multi_lang_ref);

	free(this);
}


/************************* modul view ***********************************/
view * view_new(controler * controler_ref)
{
	view * this = (view*) malloc(sizeof(view));

	this->controler_ref = controler_ref;

	view_initialize_base_class(this);
	view_build_main_window(this);

	view_build_alarm_widget(this);

	view_build_screens(this);
	view_pack_screens(this);

	view_load_company_icon(this);

	view_pack_container(this);

	g_timeout_add(CONF_CYCLIC_INTERUPT_INTERVAL, view_cyclic_interupt, this);

	return this;
}


gboolean view_cyclic_interupt(gpointer param)
{
	view * this = (view*) param;

	gtk_widget_queue_draw(GTK_WIDGET(this->window));

	return TRUE;
}


void view_hide_cursor(view * this)
{
	GdkCursor * cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_BLANK_CURSOR);
	GdkWindow * win = gtk_widget_get_window((this->window));
	gdk_window_set_cursor((win), cursor);
}

void view_initialize(view * this)
{
	view_base_show_order_screen(this->view_base_ref);
	gtk_widget_show_all(this->window);
	//view_hide_cursor(this);
}

void view_build_main_window(view * this)
{
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size(GTK_WINDOW(this->window), 
					this->view_base_ref->screen_geometry.width, 
					this->view_base_ref->screen_geometry.height);

	gtk_window_set_title(GTK_WINDOW(this->window), CONF_WINDOW_TITLE);
	gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_fullscreen (GTK_WINDOW(this->window));
	gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);

	this->container = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(this->window), this->container);
}

GtkWidget * view_initialize_company_icon_widget(GdkPixbuf * icon, double window_width_ratio)
{
	GdkPixbuf * scale_icon = view_base_scale_icon(icon, x_axis, 150*window_width_ratio);

	GtkWidget * company_icon = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(company_icon), gtk_image_new_from_pixbuf(scale_icon));

	gtk_widget_set_size_request(GTK_WIDGET(company_icon), 
					gdk_pixbuf_get_width(scale_icon), 
					gdk_pixbuf_get_height(scale_icon));

	gtk_widget_add_events(company_icon, GDK_BUTTON_PRESS_MASK);

	return company_icon;
}

bool view_load_company_icon(view * this)
{
	GdkPixbuf * icon = view_base_load_image(CONF_COMPANY_ICON_PATH);

	if(icon != NULL)
	{
		this->company_icon = view_initialize_company_icon_widget(icon, this->view_base_ref->window_width_ratio);
		g_object_unref(icon);

		return true;
	}
	else
	{
		this->company_icon = NULL;

		return false;
	}
}

void view_initialize_base_class(view * this)
{
	geometry window_base_geometry = {800, 600};

	this->view_base_ref = view_base_new(this->controler_ref, window_base_geometry);
	view_base_set_current_window_geometry(this->view_base_ref, 
						this->view_base_ref->screen_geometry);
}

void view_build_screens(view * this)
{
	this->view_bill_viewer_screen_ref = view_bill_viewer_screen_new(this->view_base_ref);
	this->view_order_screen_ref = view_order_screen_new(this->view_base_ref);
	this->view_manual_input_screen_ref = view_manual_input_screen_new(this->view_base_ref);
	this->view_settings_screen_ref = view_settings_screen_new(this->view_base_ref);
	this->view_order_finish_screen_ref = view_order_finish_screen_new(this->view_base_ref);
}

void view_build_alarm_widget(view * this)
{
	geometry widget_geometry;
	widget_geometry.width = this->view_base_ref->window_geometry.width;
	widget_geometry.height = view_base_recount_y_geometry_by_ratio(this->view_base_ref, 25);

	this->alarm_widget_ref = alarm_widget_new(this->view_base_ref->controler_ref->alarm_buffer_ref, widget_geometry);

}

void view_pack_screens(view * this)
{
	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container),
				this->view_order_screen_ref->base_screen_ref->container,
				"order_screen");

	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container), 
				this->view_bill_viewer_screen_ref->base_screen_ref->container, 
				"bill_viewer_screen");

	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container),
				this->view_manual_input_screen_ref->base_screen_ref->container,
				"manual_input_screen");

	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container), 
				this->view_settings_screen_ref->base_screen_ref->container,
				"settings_screen");

	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container),
				this->view_order_finish_screen_ref->base_screen_ref->container,
				"order_finish_screen");
}

void view_pack_container(view * this)
{
	if(this->company_icon != NULL)
	{
		uint32_t window_base_width = this->view_base_ref->window_base_geometry.width;

		gtk_fixed_put(GTK_FIXED(this->container), 
				this->company_icon, 
				view_base_recount_x_geometry_by_ratio(this->view_base_ref, (window_base_width-200)/2+25),
				view_base_recount_y_geometry_by_ratio(this->view_base_ref, 30));	
	}

	gtk_fixed_put(GTK_FIXED(this->container), 
			this->alarm_widget_ref->draw_area,
			0,
			view_base_recount_y_geometry_by_ratio(this->view_base_ref, 100));

	gtk_fixed_put(GTK_FIXED(this->container),
			this->view_base_ref->stack_container,
			0,
			view_base_recount_y_geometry_by_ratio(this->view_base_ref, 125));
}  

void view_signals(view * this)
{
	g_signal_connect(G_OBJECT(this->window), 
				"destroy", 
				G_CALLBACK(view_window_exit_callback), 
				this);

	g_signal_connect(G_OBJECT(this->company_icon), 
				"button_press_event", 
				G_CALLBACK(view_close_callback),
			       	this);

	view_bill_viewer_screen_signals(this->view_bill_viewer_screen_ref);
	view_order_screen_signals(this->view_order_screen_ref);
	view_manual_input_screen_signals(this->view_manual_input_screen_ref);
	view_settings_screen_signals(this->view_settings_screen_ref);
	view_order_finish_screen_signals(this->view_order_finish_screen_ref);

	alarm_widget_signals(this->alarm_widget_ref);
}

void view_finalize(view * this)
{
	view_bill_viewer_screen_finalize(this->view_bill_viewer_screen_ref);
	view_order_screen_finalize(this->view_order_screen_ref);
	view_manual_input_screen_finalize(this->view_manual_input_screen_ref);
	view_settings_screen_finalize(this->view_settings_screen_ref);
	view_order_finish_screen_finalize(this->view_order_finish_screen_ref);

	view_base_finalize(this->view_base_ref);

	gtk_main_quit();
}


void view_window_exit_callback(GtkWidget * widget, gpointer param)
{
	view * this = (view*) param;
	view_finalize(this);
}

void view_close_callback(GtkWidget * widget, GdkEventButton * event, gpointer * param)
{
	if(event->type == GDK_2BUTTON_PRESS)
	{
		view * this = (view*) param;
		view_finalize(this);
	}
}

/*************************** modul view_base_screen ****************************/


view_base_screen * view_base_screen_new(view_base * view_base_ref)
{
	view_base_screen * this = (view_base_screen*) malloc(sizeof(view_base_screen));

	this->view_base_ref = view_base_ref;
	this->container = gtk_fixed_new();

	return this;
}

GtkWidget * view_base_screen_build_button(view_base_screen * this, double width, double height)
{
	GtkWidget * button = gtk_button_new_with_label("");
	gtk_widget_set_can_focus (GTK_WIDGET(button), FALSE);

	gtk_widget_set_size_request(GTK_WIDGET(button), 
					view_base_recount_x_geometry_by_ratio(this->view_base_ref, width), 
					view_base_recount_y_geometry_by_ratio(this->view_base_ref, height));

	return button;
}

GtkWidget * view_base_screen_build_label(view_base_screen * this, double width, double height, float xalign)
{
	GtkWidget * label = gtk_label_new(NULL);
	
	gtk_widget_set_size_request(GTK_WIDGET(label), 
					view_base_recount_x_geometry_by_ratio(this->view_base_ref, width),
		       			view_base_recount_y_geometry_by_ratio(this->view_base_ref, height));
	gtk_label_set_xalign(GTK_LABEL(label), xalign);

	return label;
}


void view_base_screen_finalize(view_base_screen * this)
{
	free(this);
}

/*************************** modul multi_lang *********************************/

multi_lang * multi_lang_new()
{
	multi_lang * this = (multi_lang*) malloc(sizeof(multi_lang));

	this->language_index = lang_cz;
	this->lang_struct = (lang **) malloc(sizeof(lang*));

	multi_lang_initialize_language_structure(this);

	multi_lang_initialize_czech_text(this);

	return this;
}

void multi_lang_initialize_language_structure(multi_lang * this)
{
	for(uint8_t i; i < lang_num; i++)
	{
		this->lang_struct[i] = (lang*) malloc(sizeof(lang));
	}
}

void multi_lang_initialize_czech_text(multi_lang * this)
{
	lang * lang_struct_cz = this->lang_struct[lang_cz];

	lang_struct_cz->language_name = "Čeština";

	multi_lang_set_alarm_text_czech(lang_struct_cz);
	multi_lang_set_order_screen_text_czech(lang_struct_cz);
	multi_lang_set_manual_input_screen_text_czech(lang_struct_cz);
	multi_lang_set_order_finish_screen_text_czech(lang_struct_cz);
	multi_lang_set_settings_screen_text_czech(lang_struct_cz);
	multi_lang_set_bill_viewer_screen_text_czech(lang_struct_cz);
}

void multi_lang_set_alarm_text_czech(lang * this)
{

}

void multi_lang_set_order_screen_text_czech(lang * this)
{
	this->btn_clear_order_text = "Nová platba";
	this->btn_increase_quantity_text = "+1";
	this->btn_decrease_quantity_text = "-1";
	this->btn_pay_text = "Zaplatit";
	this->btn_manual_input_text = "Zadat ručně";
	this->lbl_sum_text = "Celkem:";
	this->currency_text = "Kč";
	this->default_sum_price_text = "0.0 Kč";
	this->order_list_widget_goods_text = "Zboží";
	this->order_list_widget_quantity_text = "Množství";
	this->order_list_widget_price_without_tax_text = "Cena bez DPH";
	this->order_list_widget_price_with_tax_text = "Cena s DPH";
}

void multi_lang_set_manual_input_screen_text_czech(lang * this)
{
	this->btn_prev_text = "Předchozí";
	this->btn_back_text = "Zpět";
	this->btn_next_text = "Další";
}

void multi_lang_set_order_finish_screen_text_czech(lang * this)
{
	this->btn_print_bill_text = "Vytisknout\núčtenku";
	this->btn_finish_text = "Dokončit\nobjednávku";

	this->lbl_customer_payed_text = "Zaplaceno:";
	this->lbl_order_sum_text = "Celkem k zaplacení:";
	this->lbl_money_back_text = "Na zpět:";
}

void multi_lang_set_settings_screen_text_czech(lang * this)
{

}

void multi_lang_set_bill_viewer_screen_text_czech(lang * this)
{

}

lang * multi_lang_get_current_language(multi_lang * this)
{
	if(this->language_index < lang_num)
		return this->lang_struct[this->language_index];
	else
		return NULL;
}

void multi_lang_release_language_structures(multi_lang * this)
{
	for(uint8_t i; i< lang_num; i++)
	{
		free(this->lang_struct[i]);
	}
}

void multi_lang_finalize(multi_lang * this)
{
	multi_lang_release_language_structures(this);

	free(this);
}


/**************************** modul view_bill_viewer_screen ***********************/

view_bill_viewer_screen * view_bill_viewer_screen_new(view_base * view_base_ref)
{
	view_bill_viewer_screen * this = (view_bill_viewer_screen *) malloc(sizeof(view_bill_viewer_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_bill_viewer_screen_build_widgets(this);
	view_bill_viewer_screen_language(this);
	view_bill_viewer_screen_pack_widgets(this);

	return this;
}

void view_bill_viewer_screen_build_widgets(view_bill_viewer_screen * this)
{

}

void view_bill_viewer_screen_language(view_bill_viewer_screen * this)
{

}

void view_bill_viewer_screen_pack_widgets(view_bill_viewer_screen * this)
{

}

void view_bill_viewer_screen_signals(view_bill_viewer_screen * this)
{

}

void view_bill_viewer_screen_finalize(view_bill_viewer_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

/********************** modul view_order_screen *********************************/

view_order_screen * view_order_screen_new(view_base * view_base_ref)
{
	view_order_screen * this = (view_order_screen *) malloc(sizeof(view_order_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_order_screen_build_widgets(this);
	view_order_screen_language(this);
	view_order_screen_pack_widgets(this);

	return this;
}

GtkTreeViewColumn * view_order_screen_add_header_column(uint32_t position, const char * title)
{
	GtkCellRenderer * renderer = gtk_cell_renderer_text_new();
	g_object_set(renderer, "size", 20, NULL);

	GtkTreeViewColumn * column = gtk_tree_view_column_new_with_attributes(title, renderer, NULL);


	gboolean size_set;
	int size;

	g_object_get(renderer, "size", &size, "size-set", &size_set, NULL);
	printf("%d - %s\n", size, ((size_set == TRUE) ? "true": "false"));

	gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), FALSE);
	gtk_tree_view_column_set_min_width (column, 20);
	gtk_tree_view_column_set_expand (column, TRUE);

	return column;
}

void view_order_screen_build_list_widget(view_order_screen * this)
{
	geometry window_base_geometry = this->base_screen_ref->view_base_ref->window_base_geometry;

	GtkTreeStore * store = gtk_tree_store_new(N_COLUMNS,
						G_TYPE_STRING,
						G_TYPE_INT,
						G_TYPE_DOUBLE,
						G_TYPE_DOUBLE);

	this->list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	gtk_widget_set_can_focus (GTK_WIDGET(this->list), FALSE);
	g_object_unref (G_OBJECT (store));

	this->scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(this->scroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(this->scroll), this->list);
	gtk_widget_set_can_focus (GTK_WIDGET(this->scroll), FALSE);
	gtk_widget_set_size_request(GTK_WIDGET(this->scroll), 
			view_base_recount_x_geometry_by_ratio(this->base_screen_ref->view_base_ref, window_base_geometry.width-100),
			view_base_recount_y_geometry_by_ratio(this->base_screen_ref->view_base_ref, window_base_geometry.height-125-160));

}

void view_order_screen_build_widgets(view_order_screen * this)
{
	double widget_height = 50;
	double button_width_short = 50;
	double button_width_long = 100;

	view_order_screen_build_list_widget(this);

	this->btn_clear_order = view_base_screen_build_button(this->base_screen_ref, button_width_long, widget_height);
	this->btn_increase_quantity = view_base_screen_build_button(this->base_screen_ref, button_width_short, widget_height);
	this->btn_decrease_quantity = view_base_screen_build_button(this->base_screen_ref, button_width_short, widget_height);
	this->btn_pay = view_base_screen_build_button(this->base_screen_ref, button_width_long, widget_height);
	this->btn_manual_input = view_base_screen_build_button(this->base_screen_ref, button_width_long, widget_height);

	this->lbl_order_sum = view_base_screen_build_label(this->base_screen_ref, 
							100,
							widget_height, 
							0);

	this->lbl_sum_price = view_base_screen_build_label(this->base_screen_ref,
								200,
								widget_height, 
								1);
}

void view_order_screen_language(view_order_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * btn_label;

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_clear_order));
	view_base_screen_set_label_markup_text(btn_label, cz_lang->btn_clear_order_text, 20);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_increase_quantity));
	view_base_screen_set_label_markup_text(btn_label, cz_lang->btn_increase_quantity_text, 20);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_decrease_quantity));
	view_base_screen_set_label_markup_text(btn_label, cz_lang->btn_decrease_quantity_text, 20);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_pay));
	view_base_screen_set_label_markup_text(btn_label, cz_lang->btn_pay_text, 20);
	
	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_manual_input));
	view_base_screen_set_label_markup_text(btn_label, cz_lang->btn_manual_input_text, 20);

	view_base_screen_set_label_markup_text(this->lbl_order_sum, cz_lang->lbl_sum_text, 20);
	view_base_screen_set_label_markup_text(this->lbl_sum_price, cz_lang->default_sum_price_text, 20);


	gtk_tree_view_append_column(GTK_TREE_VIEW(this->list), 
				view_order_screen_add_header_column(GOODS_COLUMN, cz_lang->order_list_widget_goods_text));
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->list), 
				view_order_screen_add_header_column(QUANTITY_COLUMN, cz_lang->order_list_widget_quantity_text));
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->list), 
				view_order_screen_add_header_column(PRICE_WITHOUT_TAX_COLUMN, cz_lang->order_list_widget_price_without_tax_text));
	gtk_tree_view_append_column(GTK_TREE_VIEW(this->list), 
				view_order_screen_add_header_column(PRICE_WITH_TAX_COLUMN, cz_lang->order_list_widget_price_with_tax_text));
}

void view_order_screen_pack_widgets(view_order_screen * this)
{
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	geometry window_base_geometry = view_base_ref->window_base_geometry;
	double buttons_line_position = view_base_recount_y_geometry_by_ratio(view_base_ref, 
							window_base_geometry.height-125-50-20);
	double labels_line_position = view_base_recount_y_geometry_by_ratio(view_base_ref, 20);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_manual_input, 
			view_base_recount_x_geometry_by_ratio(view_base_ref, (window_base_geometry.width-100)/2), 
			buttons_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_clear_order,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 150),
			buttons_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_pay,
			view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-250),
			buttons_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_increase_quantity,
			view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-100),
			buttons_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_decrease_quantity,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			buttons_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->lbl_order_sum, 
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			labels_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->lbl_sum_price, 
			view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-250),
			labels_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->scroll,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, 80));
}

void view_order_screen_signals(view_order_screen * this)
{
	g_signal_connect(G_OBJECT(this->btn_manual_input), 
			"clicked", 
			G_CALLBACK(view_order_screen_btn_manual_input_click_callback), 
			this->base_screen_ref->view_base_ref);

	g_signal_connect(G_OBJECT(this->btn_pay), 
			"clicked",
			G_CALLBACK(view_order_screen_btn_pay_click_callback), 
			this->base_screen_ref->view_base_ref);

	g_signal_connect(G_OBJECT(this->btn_increase_quantity), 
			"clicked",
			G_CALLBACK(view_order_screen_btn_increase_quantity_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->btn_decrease_quantity),
			"clicked",
			G_CALLBACK(view_order_screen_btn_decrease_quantity_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->btn_clear_order), 
			"clicked",
			G_CALLBACK(view_order_screen_btn_clear_order_click_callback),
			this);

}

void view_order_screen_btn_manual_input_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_manual_input_screen((view_base*) param);
}


void view_order_screen_btn_increase_quantity_click_callback(GtkWidget * widget, gpointer param)
{
	
}

void view_order_screen_btn_decrease_quantity_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_screen_btn_pay_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_order_finish_screen((view_base*) param);
}

void view_order_screen_btn_clear_order_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_screen_finalize(view_order_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

/************************ modul view_manual_input_screen ***********************/

view_manual_input_screen * view_manual_input_screen_new(view_base * view_base_ref)
{
	view_manual_input_screen * this = (view_manual_input_screen *) malloc(sizeof(view_manual_input_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_manual_input_screen_build_widgets(this);
	view_manual_input_screen_language(this);
	view_manual_input_screen_pack_widgets(this);

	return this;
}

void view_manual_input_screen_build_widgets(view_manual_input_screen * this)
{
	double btn_width = 150;
	double btn_height = 50;

	this->button_matrix = (GtkWidget ***) malloc(sizeof(GtkWidget **)*3);

	for(int i = 0; i<3; i++)
	{
		this->button_matrix[i] = (GtkWidget **) malloc(sizeof(GtkWidget*)*5);

		for(int j = 0; j < 5; j++)
		{
			this->button_matrix[i][j] = view_base_screen_build_button(this->base_screen_ref, 150, 50);
			gtk_widget_set_sensitive(GTK_WIDGET(this->button_matrix[i][j]), FALSE);
		}
	}

	this->btn_next = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
	this->btn_prev = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
	this->btn_back = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
}

void view_manual_input_screen_language(view_manual_input_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * button_label;
	
	button_label = gtk_bin_get_child(GTK_BIN(this->btn_prev));
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_prev_text, 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_back));
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_back_text, 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_next));
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_next_text, 20);
}

void view_manual_input_screen_pack_widgets(view_manual_input_screen * this)
{
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	geometry base_window_geometry = view_base_ref->window_base_geometry;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			double x_position = view_base_recount_x_geometry_by_ratio(view_base_ref, 
									base_window_geometry.width/2-75 - 200 +(200*i));
			double y_position = view_base_recount_y_geometry_by_ratio(view_base_ref, 
									30+70*j);	

			gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
					this->button_matrix[i][j],
					x_position,
					y_position);
		}
	}


	double btn_horizontal_line_position = view_base_recount_y_geometry_by_ratio(view_base_ref, 410);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_prev,
			view_base_recount_x_geometry_by_ratio(view_base_ref, base_window_geometry.width/2-75 - 200),
			btn_horizontal_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_back,
			view_base_recount_x_geometry_by_ratio(view_base_ref, base_window_geometry.width/2-75),
			btn_horizontal_line_position);

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->btn_next,
			view_base_recount_x_geometry_by_ratio(view_base_ref, base_window_geometry.width/2-75 + 200),
			btn_horizontal_line_position);


}

void view_manual_input_screen_signals(view_manual_input_screen * this)
{
	g_signal_connect(G_OBJECT(this->btn_prev), 
			"clicked",
			G_CALLBACK(view_manual_input_screen_btn_prev_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->btn_back),
			"clicked",
			G_CALLBACK(view_manual_input_screen_btn_back_click_callback),
			this->base_screen_ref->view_base_ref);

	g_signal_connect(G_OBJECT(this->btn_next),
			"clicked",
			G_CALLBACK(view_manual_input_screen_btn_next_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][0]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_0x0_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][1]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_0x1_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][2]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_0x2_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][3]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_0x3_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][4]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_0x4_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][0]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_1x0_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][1]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_1x1_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][2]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_1x2_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][3]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_1x3_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][4]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_1x4_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][0]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_2x0_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][1]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_2x1_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][2]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_2x2_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][3]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_2x3_clicked_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][4]),
			"clicked",
			G_CALLBACK(view_manual_input_screen_button_metrix_2x4_clicked_callback),
			this);
}

void view_manual_input_screen_btn_prev_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_btn_back_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_order_screen((view_base*) param);
}

void view_manual_input_screen_btn_next_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_0x0_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_0x1_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_0x2_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_0x3_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_0x4_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_1x0_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_1x1_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_1x2_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_1x3_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_1x4_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_2x0_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_2x1_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_2x2_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_2x3_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_button_metrix_2x4_clicked_callback(GtkWidget * widget, gpointer param)
{

}

void view_manual_input_screen_finalize(view_manual_input_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}


/*************************** modul view_settings_screen ***************************/

view_settings_screen * view_settings_screen_new(view_base * view_base_ref)
{
	view_settings_screen * this = (view_settings_screen*) malloc(sizeof(view_settings_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_settings_screen_build_widgets(this);
	view_settings_screen_language(this);
	view_settings_screen_pack_widgets(this);

	return this;
}

void view_settings_screen_build_widgets(view_settings_screen * this)
{

}

void view_settings_screen_language(view_settings_screen * this)
{

}

void view_settings_screen_pack_widgets(view_settings_screen * this)
{

}

void view_settings_screen_signals(view_settings_screen * this)
{

}

void view_settings_screen_finalize(view_settings_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

view_order_finish_screen * view_order_finish_screen_new(view_base * view_base_ref)
{
	view_order_finish_screen * this = (view_order_finish_screen *) malloc(sizeof(view_order_finish_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_order_finish_screen_build_widgets(this);
	view_order_finish_screen_language(this);
	view_order_finish_screen_pack_widgets(this);

	return this;
}

void view_order_finish_screen_build_widgets(view_order_finish_screen * this)
{
	this->button_matrix = (GtkWidget ***) malloc(sizeof(GtkWidget**)*4);

	for(int i = 0; i < 4; i++)
	{
		this->button_matrix[i] = (GtkWidget **) malloc(sizeof(GtkWidget*)*3);

		for(int j = 0; j < 3; j++)
		{
			this->button_matrix[i][j] = view_base_screen_build_button(this->base_screen_ref, 50, 50);
		}
	}
	
	this->btn_print_bill = view_base_screen_build_button(this->base_screen_ref, 120, 50);
	this->btn_back = view_base_screen_build_button(this->base_screen_ref, 120, 50);
	this->btn_finish = view_base_screen_build_button(this->base_screen_ref, 120, 50);

	geometry value_widget_geometry;
	value_widget_geometry.width = view_base_recount_x_geometry_by_ratio(this->base_screen_ref->view_base_ref, this->base_screen_ref->view_base_ref->window_base_geometry.width-100);
	value_widget_geometry.height = view_base_recount_y_geometry_by_ratio(this->base_screen_ref->view_base_ref, 30);

	double bg_color_1[3] = {0.84, 0.84, 0.84};
	double bg_color_2[3] = {0.91, 0.91, 0.91};

	this->order_sum_price = value_widget_new(value_widget_geometry);
	value_widget_set_font_size(this->order_sum_price, 30);
	value_widget_set_left_padding(this->order_sum_price, 30);
	value_widget_set_right_padding(this->order_sum_price, 30);
	value_widget_set_font_family(this->order_sum_price, "Arial");
	value_widget_set_background_color(this->order_sum_price, bg_color_2);

	this->customer_payed = value_widget_new(value_widget_geometry);
	value_widget_set_font_size(this->customer_payed, 30);
	value_widget_set_left_padding(this->customer_payed, 30);
	value_widget_set_right_padding(this->customer_payed, 30);
	value_widget_set_font_family(this->customer_payed, "Arial");
	value_widget_set_background_color(this->customer_payed, bg_color_1);

	this->count_money_back = value_widget_new(value_widget_geometry);
	value_widget_set_background_color(this->count_money_back, bg_color_2);
	value_widget_set_font_size(this->count_money_back, 30);
	value_widget_set_left_padding(this->count_money_back, 30);
	value_widget_set_right_padding(this->count_money_back, 30);
	value_widget_set_font_family(this->count_money_back, "Arial");

}


void view_order_finish_screen_language(view_order_finish_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * button_label;
	
	button_label = gtk_bin_get_child(GTK_BIN(this->btn_print_bill));
	gtk_label_set_justify(GTK_LABEL(button_label), GTK_JUSTIFY_CENTER);
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_print_bill_text, 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_back));
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_back_text, 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_finish));
	gtk_label_set_justify(GTK_LABEL(button_label), GTK_JUSTIFY_CENTER);
	view_base_screen_set_label_markup_text(button_label, cz_lang->btn_finish_text, 20);

	value_widget_set_label(this->order_sum_price, cz_lang->lbl_order_sum_text);
	value_widget_set_label(this->customer_payed, cz_lang->lbl_customer_payed_text);
	value_widget_set_label(this->count_money_back, cz_lang->lbl_money_back_text);

	value_widget_set_value(this->order_sum_price, (char*) cz_lang->default_sum_price_text);
	value_widget_set_value(this->customer_payed, (char*) cz_lang->default_sum_price_text);
	value_widget_set_value(this->count_money_back, (char*) cz_lang->default_sum_price_text);


	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][0]));
	view_base_screen_set_label_markup_text(button_label, "C", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][1]));
	view_base_screen_set_label_markup_text(button_label, "CE", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][2]));
	view_base_screen_set_label_markup_text(button_label, "0", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][0]));
	view_base_screen_set_label_markup_text(button_label, "1", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][1]));
	view_base_screen_set_label_markup_text(button_label, "4", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][2]));
	view_base_screen_set_label_markup_text(button_label, "7", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][0]));
	view_base_screen_set_label_markup_text(button_label, "2", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][1]));
	view_base_screen_set_label_markup_text(button_label, "5", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][2]));
	view_base_screen_set_label_markup_text(button_label, "8", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][0]));
	view_base_screen_set_label_markup_text(button_label, "3", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][1]));
	view_base_screen_set_label_markup_text(button_label, "6", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][2]));
	view_base_screen_set_label_markup_text(button_label, "9", 20);
}

void view_order_finish_screen_pack_widgets(view_order_finish_screen * this)
{
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	geometry window_base_geometry = view_base_ref->window_base_geometry;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j ++)
		{
			double button_x_position = view_base_recount_x_geometry_by_ratio(view_base_ref, 
								window_base_geometry.width-310+(70*i));
			double button_y_position = view_base_recount_y_geometry_by_ratio(view_base_ref, 
								window_base_geometry.height-430+(70*j));

			gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
					this->button_matrix[i][j],
					button_x_position,
					button_y_position);
		}
	}

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container),
			this->btn_finish,
			view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-50-120),
			view_base_recount_y_geometry_by_ratio(view_base_ref, window_base_geometry.height-125-80));

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container),
			this->btn_back,
			view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-50-260),
			view_base_recount_y_geometry_by_ratio(view_base_ref, window_base_geometry.height-125-80));

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container),
			this->btn_print_bill,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, window_base_geometry.height-125-80));



	/*
	 *
	GtkWidget * lbl_sum = view_base_screen_build_label(this->base_screen_ref, 200, 50, 0);
	GtkWidget * lbl_payed = view_base_screen_build_label(this->base_screen_ref, 200, 50, 0);
	GtkWidget * lbl_money_back = view_base_screen_build_label(this->base_screen_ref, 200, 50, 0);
	GtkWidget * lbl_sum_price = view_base_screen_build_label(this->base_screen_ref, 200, 50, 1);
	GtkWidget * lbl_count_money_back = view_base_screen_build_label(this->base_screen_ref, 200, 50, 1);

	this->entry_payed = gtk_entry_new();
	 */ 
	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->order_sum_price->draw_area,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, 20));

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->customer_payed->draw_area,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, 70));

	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			this->count_money_back->draw_area,
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, 120));
}

void view_order_finish_screen_signals(view_order_finish_screen * this)
{
	g_signal_connect(G_OBJECT(this->btn_print_bill), 
			"clicked",
			G_CALLBACK(view_order_finish_screen_btn_print_bill_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->btn_back),
			"clicked",
			G_CALLBACK(view_order_finish_screen_btn_back_click_callback),
			this->base_screen_ref->view_base_ref);

	g_signal_connect(G_OBJECT(this->btn_finish),
			"clicked",
			G_CALLBACK(view_order_finish_screen_btn_finish_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][0]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_0x0_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][1]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_0x1_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[0][2]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_0x2_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][0]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_1x0_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][1]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_1x1_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[1][2]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_2x2_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][0]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_2x0_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][1]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_2x1_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[2][2]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_2x2_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[3][0]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_3x0_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[3][1]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_3x1_click_callback),
			this);

	g_signal_connect(G_OBJECT(this->button_matrix[3][2]),
			"clicked",
			G_CALLBACK(view_order_finish_screen_button_matrix_3x2_click_callback),
			this);
}


void view_order_finish_screen_btn_print_bill_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_btn_back_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_order_screen((view_base *) param);
}

void view_order_finish_screen_btn_finish_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen * this = (view_order_finish_screen *) param;
	view_base_show_order_screen(this->base_screen_ref->view_base_ref);
}


void view_order_finish_screen_button_matrix_0x0_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_0x1_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_0x2_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_1x0_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_1x1_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_1x2_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_2x0_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_2x1_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_2x2_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_3x0_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_3x1_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_button_matrix_3x2_click_callback(GtkWidget * widget, gpointer param)
{

}

void view_order_finish_screen_finalize(view_order_finish_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

/**************************** modul alarm_widget ****************************/

alarm_widget * alarm_widget_new(alarm_buffer * alarm_buffer_ref, geometry widget_geometry)
{
	alarm_widget * this = (alarm_widget *) malloc(sizeof(alarm_widget));

	this->alarm_buffer_ref = alarm_buffer_ref;
	this->widget_geometry.width = widget_geometry.width;
	this->widget_geometry.height = widget_geometry.height;
	this->blink = false;

	alarm_widget_build(this);

	return this;
}

gboolean alarm_widget_draw_callback(GtkWidget * drawing_area, cairo_t * cr, gpointer param)
{
	alarm_widget * this = (alarm_widget*) param;

	if(this->alarm_buffer_ref->error == true)
	{
		gtk_widget_set_visible(GTK_WIDGET(this->draw_area), TRUE);

		if(this->blink == true)
			cairo_set_source_rgb(cr, 1,0,0);
		else
			cairo_set_source_rgb(cr, 1,0.60,0.1);

		this->blink = !this->blink;
	}
	else if(this->alarm_buffer_ref->warning == true)
	{
		gtk_widget_set_visible(GTK_WIDGET(this->draw_area), TRUE);
		cairo_set_source_rgb(cr, 1,0.5,0.5);
	}
	else
	{
		gtk_widget_set_visible(GTK_WIDGET(this->draw_area), FALSE);
	}

	cairo_rectangle(cr, 0,0, this->widget_geometry.width, this->widget_geometry.height);

	cairo_fill(cr);

	/*
	cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
	cairo_set_font_size(cr, this->height/2);
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	//cairo_move_to(cr, );
	//cairo_show_text(cr, );

	cairo_stroke(cr);
*/
	return FALSE;
}

void alarm_widget_build(alarm_widget * this)
{
	this->draw_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), 
				this->widget_geometry.width, 
				this->widget_geometry.height);
	gtk_widget_add_events(GTK_WIDGET(this->draw_area), GDK_BUTTON_PRESS_MASK);
}

void alarm_widget_signals(alarm_widget * this)
{
	g_signal_connect(G_OBJECT(this->draw_area), 
				"draw", 
				G_CALLBACK(alarm_widget_draw_callback), 
				this);

	g_signal_connect(G_OBJECT(this->draw_area), 
				"button_press_event", 
				G_CALLBACK(alarm_widget_reset_error_buffer_callback), 
				this->alarm_buffer_ref);
}

void alarm_widget_reset_error_buffer_callback(GtkWidget * widget, GdkEventButton * event, gpointer param)
{
	alarm_buffer * this = (alarm_buffer*) param;
	alarm_buffer_reset_error(this);
}

void alarm_widget_finalize(alarm_widget * this)
{
	free(this);
}


/*************************** modul value_widget *******************************/

value_widget * value_widget_new(geometry widget_geometry)
{
	value_widget * this = (value_widget *) malloc(sizeof(value_widget));

	this->widget_geometry.width = widget_geometry.width;
	this->widget_geometry.height = widget_geometry.height;

	this->label = NULL;
	this->value = NULL;

	this->font_size = 12;
	this->font_family = NULL;

	this->left_padding = 10;
	this->right_padding = 10;

	this->bg_color[0] = 1.0;
	this->bg_color[1] = 1.0;
	this->bg_color[2] = 1.0;

	this->fg_color[0] = 0.0;
	this->fg_color[1] = 0.0;
	this->fg_color[2] = 0.0;

	this->draw_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), widget_geometry.width, widget_geometry.height);

	value_widget_signals(this);

	return this;
}


void value_widget_set_geometry(value_widget * this, geometry widget_geometry)
{
	this->widget_geometry.width = widget_geometry.width;
	this->widget_geometry.height = widget_geometry.height;
}

geometry value_widget_get_geometry(value_widget * this)
{
	return this->widget_geometry;
}

double * value_widget_get_forground_color(value_widget * this)
{
	return this->fg_color;
}

double * value_widget_get_background_color(value_widget * this)
{
	return this->bg_color;
}

void value_widet_set_foreground_color(value_widget * this, double fg_color[3])
{
	this->fg_color[0] = fg_color[0];
	this->fg_color[1] = fg_color[1];
	this->fg_color[2] = fg_color[2];
}

void value_widget_set_background_color(value_widget * this, double bg_color[3])
{
	this->bg_color[0] = bg_color[0];
	this->bg_color[1] = bg_color[1];
	this->bg_color[2] = bg_color[2];
}

void value_widget_set_value(value_widget * this, char * value)
{
	this->value = value;
	gtk_widget_queue_draw(GTK_WIDGET(this->draw_area));
}

char * value_widget_get_value(value_widget * this)
{
	return this->value;
}

void value_widget_set_label(value_widget * this, const char * label)
{
	this->label = label;
	gtk_widget_queue_draw(GTK_WIDGET(this->draw_area));
}

const char * value_widget_get_label(value_widget * this)
{
	return this->label;
}

gboolean value_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param)
{
	value_widget * this = (value_widget *) param;
	cairo_text_extents_t extents;

	cairo_set_source_rgb(cr, this->bg_color[0], this->bg_color[1], this->bg_color[2]);
	cairo_rectangle(cr, 0,0, this->widget_geometry.width, this->widget_geometry.height);

	cairo_fill(cr);

	cairo_set_source_rgb(cr, this->fg_color[0], this->fg_color[1], this->fg_color[2]);
	cairo_set_font_size(cr, this->font_size);
	
	if(this->font_family != NULL)
		cairo_select_font_face(cr, this->font_family, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	if(this->label != NULL)
	{
		cairo_text_extents(cr, this->label, &extents);
		cairo_move_to(cr, this->left_padding, this->widget_geometry.height/2+extents.height/4);
		cairo_show_text(cr, this->label);
	}

	if(this->value != NULL)
	{
		cairo_text_extents(cr, this->value, &extents);
		cairo_move_to(cr, this->widget_geometry.width - extents.width - this->right_padding, this->widget_geometry.height/2+extents.height/2);
		cairo_show_text(cr, this->value);
	}

	cairo_stroke(cr);

	return FALSE;
}

void value_widget_set_font_family(value_widget * this, const char * font_family)
{
	this->font_family = font_family;
}

const char * value_widget_get_font_family(value_widget * this)
{
	return this->font_family;
}

void value_widget_set_font_size(value_widget * this, uint32_t font_size)
{
	this->font_size = font_size;
}

uint32_t valie_widget_get_font_size(value_widget * this)
{
	return this->font_size;
}

void value_widget_set_left_padding(value_widget * this, uint32_t left_padding)
{
	this->left_padding = left_padding;
}

void value_widget_set_right_padding(value_widget * this, uint32_t right_padding)
{
	this->right_padding = right_padding;
}

uint32_t value_widget_get_right_padding(value_widget * this)
{	
	return this->right_padding;
}

uint32_t value_widget_get_left_padding(value_widget * this)
{
	return this->left_padding;
}

void value_widget_signals(value_widget * this)
{
	g_signal_connect(G_OBJECT(this->draw_area),
				"draw",
				G_CALLBACK(value_widget_draw_callback),
				this);
}


/********************************* modul order_list_widget **********************/


order_list_widget * order_list_widget_new(geometry widget_geometry)
{
	order_list_widget * this = (order_list_widget *) malloc(sizeof(order_list_widget));


	this->widget_geometry.width = widget_geometry.width;
	this->widget_geometry.height = widget_geometry.height;

	this->draw_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), widget_geometry.width, widget_geometry.height);

	this->column_title_list = NULL;
	this->column_title_size = 0;

	this->font_family = NULL;
	this->font_size = 12;

	this->source_order_list = FALSE;

	this->is_row_selected = false;;
	this->selected_row_index = 0;
	this->visible_row_number = 3;

	order_list_widget_signals(this);

	return this;
}

void order_list_widget_set_column_structure(order_list_widget * this, uint8_t columnt_title_size, const char ** column_title_list)
{

}

void order_list_widget_set_visible_row_number(order_list_widget * this, uint8_t visible_row_number)
{
	this->visible_row_number = visible_row_number;
}

void order_list_widget_signals(order_list_widget * this)
{
	g_signal_connect(G_OBJECT(this->draw_area), 
				"draw",
				G_CALLBACK(order_list_widget_draw_callback),
				this);

	g_signal_connect(G_OBJECT(this->draw_area),
				"button_press_event",
				G_CALLBACK(order_list_widget_click_callback),
				this);

	g_signal_connect(G_OBJECT(this->draw_area),
				"scroll_event",
				G_CALLBACK(order_list_widget_scroll_callback),
				this);
}

void order_list_widget_set_source(order_list_widget * this, order_list * source_order_list)
{
	this->source_order_list = source_order_list;
}

void order_list_widget_repaint(order_list_widget * this)
{
	gtk_widget_queue_draw(GTK_WIDGET(this->draw_area));
}

uint32_t order_list_widget_get_selected_row(order_list_widget * this)
{
	return this->selected_row_index;
}

bool order_list_widget_is_selected(order_list_widget * this)
{
	return this->is_row_selected;
}

void order_list_widget_cancel_selection(order_list_widget * this)
{
	this->is_row_selected = false;
	this->selected_row_index = 0;
}

gboolean order_list_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param)
{
	order_list_widget * this = (order_list_widget*) param;

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0,0, this->widget_geometry.width, this->widget_geometry.height);
	cairo_fill(cr);

	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	if(this->font_family != NULL)
		cairo_select_font_face(cr, this->font_family, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	if(this->column_title_list != NULL)
	{
		for(int i = 0; i < this->column_title_size; i++)
		{
			cairo_text_extents_t extent;
			cairo_text_extents(cr, this->column_title_list[i], extent);
			
			cairo_move_to(cr, );
			cairo_show_text(cr, this->column_title_list[i]);	
		}
	}

	cairo_stroke(cr);

	return FALSE;
}

gpointer order_list_widget_click_callback(GtkWidget * widget, GdkEvent * event, gpointer param)
{

	return FALSE;
}

gboolean order_list_widget_scroll_callback(GtkWidget * widget, GdkEvent * event, gpointer param)
{
	return FALSE;
}





/********************** definice unit testů **********************************/

#if TEST == TRUE

void assert(bool condition, char * comment, ...)
{
	if(condition == false)
	{
		va_list params;
		va_start(params, comment);

		vprintf(comment, params);

		va_end(params);
	}
}

void unit_test_runtime()
{
	test_case_view_base();
	//assert(false, "komentař: %d+%d=%d", 1,2,3);
}


#endif


/************************* hlavní výkonné vlákno (main) ***********************/

int main(int argv, char ** argc)
{
#if TEST == FALSE

	controler * controler_ref = NULL;
	view * view_ref = NULL;

	controler_ref = controler_new();

	if(controler_ref != NULL)
	{	
		gtk_init(&argv, &argc);

		view_ref = view_new(controler_ref);
		view_signals(view_ref);
		view_initialize(view_ref);

		gtk_main();
	}
	else
	{
		printf("Nelze inicializovat jádro!");
	}

#else
	unit_test_runtime();
#endif
	return 0;
}








