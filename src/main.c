#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <aclib.h>
#include <libpq-fe.h>
#include <math.h>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <Winspool.h>
#endif


/********************* definice konstant *******************************/

#define TEST FALSE


#define CONF_WINDOW_TITLE "Pokladní systém"
#define CONF_COMPANY_ICON_PATH "img/logo-mlyn-dubecko.png"
#define CONF_CYCLIC_INTERUPT_INTERVAL 1000

#define CONF_DB_CONNECTION ""


#define GS ((char) 0x1d) 
#define NUL ((char) 0x00)
#define ESC ((char) 0x1b)
#define EOT ((char) 4)
#define SOH ((char) 1)
#define ETX ((char) 3)

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


enum _error_index_
{
	error_index_database_connection = 0,
	error_index_unknown_order_ID,
	error_index_bill_print_error,
	error_index_stock_quantity_update_error,

	error_number
};

enum _warning_index_
{
	warning_index_unknown_position_in_order_list = 0,
	warning_index_shortage_stock,

	warning_number
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

struct _alarm_report_;
typedef struct _alarm_report_ alarm_report;

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

struct _settings_parameter_;
typedef struct _settings_parameter_ settings_parameter;

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
	c_string * print_buffer;
	uint32_t print_counter;
};

struct _alarm_report_
{
	uint32_t alarm_code;
	const char * alarm_description;
	time_t alarm_time;
};

struct _alarm_buffer_
{
	bool error;
	bool warning;

	array_list * error_buffer;
	array_list * warning_buffer;

	uint32_t error_index;
	uint32_t warning_index;

	char ** alarm_text_list;
};

struct _database_
{
	c_string * connection;
	
	char * user_name;
	char * password;
	char * db_name;
	char * tcp_port;
	char * ip_address;

	const char * current_stock;

	PGconn * conn;
};

struct _order_list_
{
	order_service * order_service_ref;

	array_list * list;
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
	uint8_t ID;
	char * item_name;
	char * item_shortcut_name;
	double item_price;
	uint32_t quantity;
	double tax;
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

	c_string * price_buffer;
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

	order_list_widget * list_widget;

	GtkWidget * btn_clear_order;
	GtkWidget * btn_increase_quantity;
	GtkWidget * btn_decrease_quantity;
	GtkWidget * btn_pay;
	GtkWidget * btn_manual_input;

	value_widget * order_sum_price;
};

struct _view_manual_input_screen_
{
	view_base_screen * base_screen_ref;
	GtkWidget *** button_matrix;

	GtkWidget * btn_next;
	GtkWidget * btn_prev;
	GtkWidget * btn_back;

	uint8_t page_index;
};


struct _settings_parameter_
{
	GtkWidget * container;
	GtkWidget * label;
	GtkWidget * entry;
};

struct _view_settings_screen_
{
	view_base_screen * base_screen_ref;

	settings_parameter ** parameter_array;
	
	GtkWidget * btn_back;
};

struct _view_order_finish_screen_
{
	view_base_screen * base_screen_ref;
	
	GtkWidget *** button_matrix;

	GtkWidget * btn_print_bill;
	GtkWidget * btn_back;
	GtkWidget * btn_finish;
	
	c_string * calculator_buffer;
	c_string * money_back_buffer;

	uint32_t calculator_register;

	value_widget * order_sum_price;
	value_widget * customer_payed;
	value_widget * count_money_back;
};

struct _alarm_widget_
{
	GtkWidget * draw_area;

	alarm_buffer * alarm_buffer_ref;

	uint32_t font_size;
	const char * font_family;

	double left_padding;

	geometry widget_geometry;

	bool blink;
};

struct _value_widget_
{
	geometry widget_geometry;

	const char * label;
	c_string * value;

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

	array_list * header_columns;

	const char * font_family;
	uint32_t font_size;

	order_list * source_order_list;
	
	GtkWidget * draw_area;
	GtkWidget * header;
	GtkWidget * scroll;
	GtkWidget * container;

	bool is_row_selected;
	uint32_t selected_row_index;

	uint8_t visible_row_number;
};


/***************** deklarace funkcí **********************************/

controler * controler_new();
uint32_t controler_get_item_number_in_stock(controler * this);
char * controler_get_item_name_by_ID(controler * this, uint8_t ID);
char * controler_get_item_shortcut_name_by_ID(controler * this, uint8_t ID);
double controler_get_item_price_by_ID(controler * this, uint8_t ID);
double controler_get_item_tax_by_ID(controler * this, uint8_t ID);
uint32_t controler_get_item_quantity_by_ID(controler * this, uint8_t ID);
void controler_increase_item_quantity_by_index(controler * this, uint32_t index);
void controler_decrease_item_quantity_by_index(controler * this, uint32_t index);
void controler_clear_order_list(controler * this);
void controler_update_order_list(controler * this, uint8_t ID);
double controler_get_order_total_price_with_tax(controler * this);
double controler_get_order_total_price_without_tax(controler * this);
uint32_t controler_get_order_list_size(controler * this);
char * controler_get_order_item_name_at_index(controler * this, uint32_t index);
uint32_t controler_get_order_item_quantity_at_index(controler * this, uint32_t index);
double controler_get_order_item_price_withou_tax_at_index(controler * this, uint32_t index);
double controler_get_order_item_price_with_tax_at_index(controler * this, uint32_t index);
static void controler_create_database_connection(controler * this);
static void controler_add_order_item(controler * this, uint8_t ID);
static void controler_build_sub_modules(controler * this);
static bool controler_database_is_connected(controler * this);
static void controler_finalize(controler * this);

user_management * user_management_new();
void user_management_finalize(user_management * this);

eet * eet_new();
void eet_finalize(eet * this);

settings * settings_new();
void settings_finalize(settings * this);

printer * printer_new();
void printer_clear_buffer(printer * this);
void printer_clear_print_counter(printer * this);
void printer_increment_print_counter(printer * this);
uint32_t printer_get_print_counter(printer * this);
bool printer_print_equest(printer * this);
void printer_finalize(printer * this);
static void printer_replace_unsupported_characters(printer * this);

alarm_report * alarm_report_new(uint32_t alarm_code, const char * alarm_description);
uint32_t alarm_report_get_code(alarm_report * this);
const char * alarm_report_get_description(alarm_report * this);
time_t alarm_report_get_time(alarm_report * this);
void alarm_report_finalize(void * this); 

alarm_buffer * alarm_buffer_new();
void alarm_buffer_set_error(alarm_buffer * this, uint32_t alarm_code);
void alarm_buffer_set_warning(alarm_buffer * this, uint32_t alarm_code);
uint32_t alarm_buffer_available_errors(alarm_buffer * this);
uint32_t alarm_buffer_available_warnings(alarm_buffer * this);
alarm_report * alarm_buffer_get_next_error_report(alarm_buffer * this);
alarm_report * alarm_buffer_get_next_warning_report(alarm_buffer * this);
void alarm_buffer_reset(alarm_buffer * this);
void alarm_buffer_finalize(alarm_buffer * this);
static alarm_report * alarm_buffer_get_next_report(array_list * buffer, uint32_t * index);
static void alarm_buffer_initialize_alarm_text_list(alarm_buffer * this);

database * database_new();
void database_set_current_stock(database * this, const char * current_stock);
bool database_connect(database * this);
void database_build_connection_string(database * this);
void database_set_user_name(database * this, char * user_name);
char * database_get_user_name(database * this);
void database_set_password(database * this, char * password);
char * database_get_password(database * this);
void database_set_db_name(database * this, char * db_name);
char * database_get_db_name(database * this);
void database_set_ip_address(database * this, char * ip_address);
char * database_get_ip_address(database * this);
void database_set_tcp_port(database * this, char * tcp_port);
char * database_get_tcp_port(database * this);
void database_disconnect(database * this);
bool database_is_connected(database * this);
void database_finalize(database * this);
uint32_t database_get_item_number_in_stock(database * this);
uint32_t database_get_item_quantity(database * this, uint8_t ID);
char * database_get_item_name(database * this, uint8_t ID);
char * database_get_item_shortcut_name(database * this, uint8_t ID);
double database_get_item_tax(database * this, uint8_t ID);
double database_get_item_price(database * this, uint8_t ID);
bool database_set_item_quantity(database * this, uint8_t ID, uint32_t new_quantity);
static void database_initialize_connection_parameters(database * this);

order_list * order_list_new();
void order_list_increment_item_quantity_by_index(order_list * this, uint32_t index);
void order_list_decrement_item_quantity_by_index(order_list * this, uint32_t index);
uint8_t order_list_get_item_ID_by_index(order_list * this, uint32_t index);
uint32_t order_list_size(order_list * this);
double order_list_get_total_price_without_tax(order_list * this);
double order_list_get_total_price_with_tax(order_list * this);
void order_list_remove_by_index(order_list * this, uint32_t index);
void order_list_clear(order_list * this);
char * order_list_get_order_item_name_at_index(order_list * this, uint32_t index);
uint32_t order_list_get_order_item_quantity_at_index(order_list * this, uint32_t index);
double order_list_get_order_item_price_withou_tax_at_index(order_list * this, uint32_t index);
double order_list_get_order_item_price_with_tax_at_index(order_list * this, uint32_t index);
void order_list_finalize(order_list * this);
uint32_t order_list_find_order_by_ID(order_list * this, uint8_t ID);
static order_item * order_list_get_order_item_by_index(order_list * this, uint8_t index);
static void order_list_decrement_item_quantity_if_not_null(order_list * this, uint32_t index);
void order_list_put_new_item_to_order_list(order_list * this, uint8_t ID, char * item_name, char * item_shortcut_name, double price, double tax);
static bool order_list_remove_item_from_list_if_quantity_equals_zero(order_list * this, order_item * item, uint32_t index);

order_service * order_service_new();
void order_service_finalize(order_service * this);

hand_scanner * hand_scanner_new();
void hand_scanner_finalize(hand_scanner * this);

order_item * order_item_new(uint8_t ID, char * item_name, char * item_shortcut_name, double item_price, double tax);
char * order_item_get_name(order_item * this);
char * order_item_get_shortcut_name(order_item * this);
double order_item_get_price(order_item * this);
uint32_t order_item_get_quantity(order_item * this);
uint8_t order_item_get_ID(order_item * this);
double order_item_get_total_price_without_tax(order_item * this);
double order_item_get_total_price_with_tax(order_item * this);
void order_item_increase_quantity(order_item * this);
void order_item_decrease_quantity(order_item * this);
void order_item_finalize(void * this);

view * view_new(controler * controler_ref);
void view_initialize(view * this);
static gboolean view_cyclic_interupt(gpointer param);
static bool view_load_company_icon(view * this);
static GtkWidget * view_initialize_company_icon_widget(GdkPixbuf * icon, double window_width_ratio);
static void view_pack_container(view * this);
static void view_hide_cursor(view * this);
static void view_build_main_window(view * this);
static void view_build_screens(view * this);
static void view_build_alarm_widget(view * this);
static void view_pack_screens(view * this);
static void view_initialize_base_class(view * this);
static void view_signals(view * this);
static void view_finalize(view * this);
static void view_window_exit_callback(GtkWidget * widget, gpointer param);
static void view_close_callback(GtkWidget * widget, GdkEventButton * event, gpointer * param);

view_base * view_base_new(controler * controler_ref, geometry window_base_geomtry);
void view_base_build_container(view_base * this);
void view_base_redraw(view_base * this);
void view_base_set_current_window_geometry(view_base * this, geometry window_geometry);
void view_base_read_current_screen_geometry(view_base * this);
void view_base_show_order_screen(view_base * this);
controler * view_base_get_controler_reference(view_base * this);
alarm_buffer * view_base_get_alarm_baffer_ref(view_base * this);
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
controler * view_base_screen_get_controler_reference(view_base_screen * this);
void view_base_screen_set_label_markup_text(GtkWidget * label, const char * string, ...);
void view_base_screen_finalize(view_base_screen * this);

multi_lang * multi_lang_new();
lang * multi_lang_get_current_language(multi_lang * this);
void multi_lang_initialize_language_structure(multi_lang * this);
void multi_lang_initialize_czech_text(multi_lang * this);
void multi_lang_set_common_text_czech(lang * this);
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
void view_order_screen_build_list_widget(view_order_screen * this);
void view_order_screen_language(view_order_screen * this);
void view_order_screen_pack_widgets(view_order_screen * this);
void view_order_screen_signals(view_order_screen * this);
gboolean view_order_screen_show_total_price_callback(GtkWidget * widget,  cairo_t * cr, gpointer param);
void view_order_screen_btn_manual_input_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_increase_quantity_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_decrease_quantity_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_pay_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_btn_clear_order_click_callback(GtkWidget * widget, gpointer param);
void view_order_screen_finalize(view_order_screen * this);

view_manual_input_screen * view_manual_input_screen_new(view_base * view_base_ref);
void view_manual_input_screen_fill(view_manual_input_screen * this);
static void view_manual_input_screen_build_widgets(view_manual_input_screen * this);
static void view_manual_input_screen_language(view_manual_input_screen * this);
static void view_manual_input_screen_pack_widgets(view_manual_input_screen * this);
static void view_manual_input_screen_signals(view_manual_input_screen * this);
static void view_manual_input_screen_btn_prev_click_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_btn_back_click_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_btn_next_click_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_0x0_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_0x1_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_0x2_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_0x3_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_0x4_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_1x0_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_1x1_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_1x2_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_1x3_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_1x4_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_2x0_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_2x1_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_2x2_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_2x3_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_button_metrix_2x4_clicked_callback(GtkWidget * widget, gpointer param);
static void view_manual_input_screen_add_item(view_manual_input_screen * this, uint8_t ID);
static void view_manual_input_screen_finalize(view_manual_input_screen * this);


settings_parameter * settings_parameter_new(geometry widget_geometry, GtkWidget * entry, double pos_label, double pos_entry);
void settings_parametr_set_label(settings_parameter * this, const char * label);
void settings_parameter_set_entry(settings_parameter * this, GtkWidget * entry);
GtkWidget * settings_parameter_get_container(settings_parameter * this);
GtkWidget * settings_parameter_get_entry(settings_parameter * this);
static void settings_parameter_build_widgets(settings_parameter * this, geometry widget_geometry, GtkWidget * entry);
static void settings_parameter_pack_widgets(settings_parameter * this, double pos_left, double pos_right);

view_settings_screen * view_settings_screen_new(view_base * view_base_ref);
void view_settings_screen_build_widgets(view_settings_screen * this);
void view_settings_screen_language(view_settings_screen * this);
void view_settings_screen_pack_widgets(view_settings_screen * this);
void view_settings_screen_signals(view_settings_screen * this);
void view_settings_screen_finalize(view_settings_screen * this);

view_order_finish_screen * view_order_finish_screen_new(view_base * view_base_ref);
void view_order_finish_screen_build_widgets(view_order_finish_screen * this);
void view_order_finish_screen_pack_widgets(view_order_finish_screen * this);
value_widget * view_order_build_value_widget(geometry widget_geometry, double bg_color[3], c_string * buffer);
void view_order_finish_screen_language(view_order_finish_screen * this);
void view_order_finish_screen_signals(view_order_finish_screen * this);
void view_order_finish_screen_count_money_back(view_order_finish_screen * this);
void view_order_finish_screen_convert_string_price(uint32_t source_register, c_string * buffer);
void view_order_finish_screen_delete_digit_in_calculator_buffer(view_order_finish_screen * this);
void view_order_finish_screen_append_digit_to_calculator_buffer(view_order_finish_screen * this, uint8_t  digit);
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
void alarm_widget_initialize_atributes(alarm_widget * this);
gboolean alarm_widget_draw_callback(GtkWidget * drawing_area, cairo_t * cr, gpointer param);
void alarm_widget_set_font_size(alarm_widget * this, uint32_t font_size);
void alarm_widget_set_font_family(alarm_widget * this, const char * font_family);
void alarm_widget_set_left_padding(alarm_widget * this, double left_padding);
void alarm_widget_reset_error_buffer_callback(GtkWidget * widget, GdkEventButton * event, gpointer param);
void alarm_widget_build(alarm_widget * this);
void alarm_widget_signals(alarm_widget * this);
void alarm_widget_finalize(alarm_widget * this);


value_widget * value_widget_new(geometry widget_geometry);
void value_widget_build_widgets(value_widget * this);
void value_widget_initialize_atributes(value_widget * this);
void value_widget_set_geometry(value_widget * this, geometry widget_geometry);
geometry value_widget_get_geometry(value_widget * this);
double * value_widget_get_forground_color(value_widget * this);
double * value_widget_get_background_color(value_widget * this);
void value_widet_set_foreground_color(value_widget * this, double fg_color[3]);
void value_widget_set_background_color(value_widget * this, double bg_color[3]);
void  value_widget_set_value(value_widget * this, c_string * value);
c_string * value_widget_get_value(value_widget * this);
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
GtkWidget * order_list_widget_get_instance(order_list_widget * this);
void order_list_widget_add_column(order_list_widget * this, const char * column_label);
void order_list_widget_set_visible_row_number(order_list_widget * this, uint8_t visible_row_number);
void order_list_widget_signals(order_list_widget * this);
void order_list_widget_set_source(order_list_widget * this, order_list * source_order_list);
void order_list_widget_repaint(order_list_widget * this);
uint32_t order_list_widget_get_selected_row(order_list_widget * this);
bool order_list_widget_is_selected(order_list_widget * this);
void order_list_widget_cancel_selection(order_list_widget * this);
gboolean order_list_widget_draw_header_column(GtkWidget * widget, cairo_t * cr, gpointer param);
void order_list_widget_draw_content(order_list_widget * this, cairo_t * cr);
void order_list_widget_set_font_size(order_list_widget * this, uint8_t font_size);
void order_list_widget_set_font_family(order_list_widget * this, const char * font_family);
void order_list_widget_initialize(order_list_widget * this);
gboolean order_list_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param);
gpointer order_list_widget_click_callback(GtkWidget * widget, GdkEventButton * event, gpointer param);
gboolean order_list_widget_scroll_callback(GtkWidget * widget, GdkEventScroll * event, gpointer param);

#if TEST == TRUE

void unit_test_runtime();
void assert(bool condition, char * comment, ...);

void tc_user_management();

void tc_eet_lib();

void tc_settings();

void tc_printer();

void tc_system_log();

void tc_database();

void tc_order_list();

void tc_order_service();

void tc_hand_scanner();

void tc_order_item();

void tc_alarm_buffer();

void tc_controler();

void tc_view_base();

void tc_multi_lang();

void tc_view_base_screen();

void tc_view_bill_browser_screen();

void tc_view_order_screen();

void tc_view_manual_input();

void tc_view_settings_screen();

void tc_view_finish_order_screen();

void tc_alarm_widget();

void tc_value_widget();

void tc_view();

#endif



/************************* hlavní výkonné vlákno (main) ***********************/
//superuser=postgrs password=asdf1234 port=5432
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
	this->settings_ref = settings_new();

	controler_create_database_connection(this);

	this->user_management_ref = user_management_new();

	this->alarm_buffer_ref = alarm_buffer_new();
}


bool controler_database_is_connected(controler * this)
{
	return database_is_connected(this->database_ref);
}

uint32_t controler_get_item_number_in_stock(controler * this)
{
	return database_get_item_number_in_stock(this->database_ref);
}

void controler_update_order_list(controler * this, uint8_t ID)
{
	uint32_t item_index = order_list_find_order_by_ID(this->order_list_ref, ID);

	if(item_index != 0xffffffff)
		order_list_increment_item_quantity_by_index(this->order_list_ref, item_index);
	else
		controler_add_order_item(this, ID);
}	

static void controler_add_order_item(controler * this, uint8_t ID)
{
	if(database_is_connected(this->database_ref) == true)
	{
		if(controler_get_item_quantity_by_ID(this, ID) > 0)
		{
			char * item_name = controler_get_item_name_by_ID(this, ID);
			char * item_shortcut_name = controler_get_item_shortcut_name_by_ID(this, ID);
			double price = controler_get_item_price_by_ID(this, ID);
			double tax = controler_get_item_tax_by_ID(this, ID);

			order_list_put_new_item_to_order_list(this->order_list_ref, ID, item_name, item_shortcut_name, price, tax);
		}
		else
		{
			alarm_buffer_set_warning(this->alarm_buffer_ref,warning_index_shortage_stock);
		}
	}
	else
	{
		alarm_buffer_set_error(this->alarm_buffer_ref,error_index_database_connection);
	}
}

double controler_get_order_total_price_with_tax(controler * this)
{
	return order_list_get_total_price_with_tax(this->order_list_ref);
}

double controler_get_order_total_price_without_tax(controler * this)
{
	return order_list_get_total_price_without_tax(this->order_list_ref);
}

uint32_t controler_get_order_list_size(controler * this)
{
	return order_list_size(this->order_list_ref);
}

char * controler_get_order_item_name_at_index(controler * this, uint32_t index)
{
	return order_list_get_order_item_name_at_index(this->order_list_ref, index);
}

uint32_t controler_get_order_item_quantity_at_index(controler * this, uint32_t index)
{
	return order_list_get_order_item_quantity_at_index(this->order_list_ref, index);
}

double controler_get_order_item_price_withou_tax_at_index(controler * this, uint32_t index)
{
	return order_list_get_order_item_price_withou_tax_at_index(this->order_list_ref, index);
}

double controler_get_order_item_price_with_tax_at_index(controler * this, uint32_t index)
{
	return order_list_get_order_item_price_with_tax_at_index(this->order_list_ref, index);
}

void controler_increase_item_quantity_by_index(controler * this, uint32_t index)
{
	uint8_t order_item_id = order_list_get_item_ID_by_index(this->order_list_ref, index);

	if(controler_get_item_quantity_by_ID(this, order_item_id) > controler_get_order_item_quantity_at_index(this, index))
		order_list_increment_item_quantity_by_index(this->order_list_ref, index);
	else
		alarm_buffer_set_warning(this->alarm_buffer_ref, warning_index_shortage_stock);
}

void controler_clear_order_list(controler * this)
{
	order_list_clear(this->order_list_ref);
}

void controler_decrease_item_quantity_by_index(controler * this, uint32_t index)
{
	order_list_decrement_item_quantity_by_index(this->order_list_ref, index);
}

uint32_t controler_get_item_quantity_by_ID(controler * this, uint8_t ID)
{
	return database_get_item_quantity(this->database_ref, ID);
}

char * controler_get_item_shortcut_name_by_ID(controler * this, uint8_t ID)
{
	return database_get_item_shortcut_name(this->database_ref, ID);
}

double controler_get_item_price_by_ID(controler * this, uint8_t ID)
{
	return database_get_item_price(this->database_ref, ID);
}

double controler_get_item_tax_by_ID(controler * this, uint8_t ID)
{
	return database_get_item_tax(this->database_ref, ID);
}

char * controler_get_item_name_by_ID(controler * this, uint8_t ID)
{
	switch(ID)
	{
		case 1:
			return "mouka 1";
		case 2: 
			return "mouka 2";
		case 3: 
			return "mouka 3";
		case 4:
			return "mouka 4";
		case 5:
			return "mouka 5";
		case 6:
			return "mouka 6";
		case 7:
			return "mouka 7";
		case 8:
			return "mouka 8";
		case 9:
			return "mouka 9";
		case 10:
			return "mouka 10";
		case 11: 
			return "mouka 11";
		case 12: 
			return "mouka 12";
		case 13:
			return "mouka 13";
		case 14:
			return "mouka 14";
		case 15:
			return "mouka 15";
		case 16:
			return "mouka 16";
		case 17:
			return "mouka 17";
		case 18:
			return "mouka 18";
		case 19:
			return "mouka 19";
		case 20:
			return "mouka 20";
		default:
			return "";
	}
}

static void controler_create_database_connection(controler * this)
{
	this->database_ref = database_new();
	database_connect(this->database_ref);
}

static void controler_finalize(controler * this)
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

	this->print_buffer = c_string_new();
	this->print_counter = 0;

	return this;
}

void printer_clear_buffer(printer * this)
{
	c_string_clear(this->print_buffer);
}

void printer_clear_print_counter(printer * this)
{
	this->print_counter = 0;
}

void printer_increment_print_counter(printer * this)
{
	this->print_counter ++;
}

bool printer_print_equest(printer * this)
{
	printer_replace_unsupported_characters(this);

	#ifdef __linux__
		FILE * printer_ref = fopen("/dev/usb/lp0", "w");
		if(printer_ref != NULL)
		{
			fprintf(printer_ref, "%s", c_string_get_char_array(this->print_buffer));
			fclose(printer_ref);
			return true;
		}
		else
		{
			return false	
		}

	#elif defined(_WIN32) || defined(_WIN64)
		return false;
	#else
		fprintf(stderr, "Unsupported platform!\n");
		return false;
	#endif	
}

uint32_t printer_get_print_counter(printer * this)
{
	return this->print_counter;
}

static void printer_replace_unsupported_characters(printer * this)
{	
	char * unsupported_characters = "ěščřžýáíéúůÉŠČŘŽÝÁÍÉÚÚ";
	char * supported_characters = "escrzyaieuuESCRZYAIEUU";

	for(int i = 0; i < c_string_len(this->print_buffer); i++)
	{
		for(int j = 0; j < strlen(unsupported_characters); j++)
		{
			if(c_string_get_char(this->print_buffer, i) == unsupported_characters[j])
			{
					c_string_set_char(this->print_buffer, j, supported_characters[j]);
					break;
			}
		}
	}
}

void printer_finalize(printer * this)
{
	c_string_finalize_v2(this->print_buffer);
	free(this);
}

/************************** modul alarm_report ***************************/

alarm_report * alarm_report_new(uint32_t alarm_code, const char * alarm_description)
{
	alarm_report * this = (alarm_report*) malloc(sizeof(alarm_report));

	this->alarm_code = alarm_code;
	this->alarm_description = alarm_description;
	this->alarm_time = time(NULL);

	return this;
}

uint32_t alarm_report_get_code(alarm_report * this)
{
	return this->alarm_code;
}

const char * alarm_report_get_description(alarm_report * this)
{
	return this->alarm_description;
}

time_t alarm_report_get_time(alarm_report * this)
{
	return this->alarm_time;
}

void alarm_report_finalize(void * this)
{
	free(this);
}



/************************** modul alarm_buffer **************************/
alarm_buffer * alarm_buffer_new()
{
	alarm_buffer * this = (alarm_buffer*) malloc(sizeof(alarm_buffer));
	
	this->error = false;
	this->warning = false;

	this->error_buffer = array_list_new();
	this->warning_buffer = array_list_new();

	this->error_index = 0;
	this->warning_index = 0;

	alarm_buffer_initialize_alarm_text_list(this);

	return this;
}

static void alarm_buffer_initialize_alarm_text_list(alarm_buffer * this)
{
	this->alarm_text_list = (char **) malloc(sizeof(char *)*(error_number+warning_number));

	this->alarm_text_list[error_index_database_connection] = "E1 Chyba spojení s databází";
	this->alarm_text_list[error_index_unknown_order_ID] = "E2 Neznámé ID objednávky";
	this->alarm_text_list[error_index_bill_print_error] = "E3 Tisk účtenky nebyl úspěšný";
	this->alarm_text_list[error_index_stock_quantity_update_error] = "E4 Chyba při aktualizaci skladových zásob";

	this->alarm_text_list[error_number+warning_index_unknown_position_in_order_list] = "W1 Neznámá pozice v objednávkovém seznamu";
	this->alarm_text_list[error_number+warning_index_shortage_stock] = "W2 Nedostatke skladových zásob";
}

void alarm_buffer_set_error(alarm_buffer * this, uint32_t alarm_code)
{
	this->error = true;

	alarm_report * report = alarm_report_new(alarm_code, this->alarm_text_list[alarm_code]);
	array_list_add(this->error_buffer, report);
}

void alarm_buffer_set_warning(alarm_buffer * this, uint32_t alarm_code)
{
	this->warning = true;

	alarm_report * report = alarm_report_new(alarm_code, this->alarm_text_list[error_number+alarm_code]);
	array_list_add(this->warning_buffer, report);
}

uint32_t alarm_buffer_available_errors(alarm_buffer * this)
{
	return array_list_size(this->error_buffer);
}

uint32_t alarm_buffer_available_warnings(alarm_buffer * this)
{
	return array_list_size(this->warning_buffer);
}

alarm_report * alarm_buffer_get_next_report(array_list * buffer, uint32_t * index)
{
	if(array_list_size(buffer) > 0)
	{
		alarm_report * report = array_list_get(buffer, *index);

		*index = (*index + 1) % array_list_size(buffer);

		return report;
	}
	else
	{
		return NULL;
	}
}

alarm_report * alarm_buffer_get_next_error_report(alarm_buffer * this)
{
	return alarm_buffer_get_next_report(this->error_buffer, &(this->error_index));
}

alarm_report * alarm_buffer_get_next_warning_report(alarm_buffer * this)
{
	return alarm_buffer_get_next_report(this->warning_buffer, &(this->warning_index));
}

void alarm_buffer_reset(alarm_buffer * this)
{
	this->error = false;
	this->warning = false;

	array_list_clear_with_release(this->error_buffer, alarm_report_finalize);
	array_list_clear_with_release(this->warning_buffer, alarm_report_finalize);

	this->error_index = 0;
	this->warning_index = 0;
}

void alarm_buffer_finalize(alarm_buffer * this)
{
	array_list_destructor_with_release_v2(this->error_buffer, alarm_report_finalize);
	array_list_destructor_with_release_v2(this->warning_buffer, alarm_report_finalize);

	free(this);
}

/************************* modul database ********************************/
database * database_new()
{
	database * this = (database*) malloc(sizeof(database));

	database_initialize_connection_parameters(this);
	this->connection = c_string_new_with_init("dbname=stock user=postgres password=asdf1234 hostaddr=127.0.0.1 port=5432");
	this->current_stock = NULL;

	return this;
}

static void database_initialize_connection_parameters(database * this)
{
	this->user_name = NULL;
	this->password = NULL;
	this->db_name = NULL;
	this->tcp_port = NULL;
	this->ip_address = NULL;
}

void database_build_connection_string(database * this)
{
	c_string_set_string(this->connection, "dbname=");
	c_string_concat(this->connection, this->db_name);
	c_string_concat(this->connection, " user=");
	c_string_concat(this->connection, this->user_name);
	c_string_concat(this->connection, " password=");
	c_string_concat(this->connection, this->password);
	c_string_concat(this->connection, " hostaddr=");
	c_string_concat(this->connection, this->ip_address);
	c_string_concat(this->connection, " port=");
	c_string_concat(this->connection, this->tcp_port);
}

void database_set_user_name(database * this, char * user_name)
{
	if(database_is_connected(this) == false)
		this->user_name = user_name;
}

char * database_get_user_name(database * this)
{
	return this->user_name;
}

void database_set_password(database * this, char * password)
{
	if(database_is_connected(this) == false)
		this->password = password;
}

char * database_get_password(database * this)
{
	return this->password;
}

void database_set_db_name(database * this, char * db_name)
{
	if(database_is_connected(this) == false)
		this->db_name = db_name;
}

char * database_get_db_name(database * this)
{
	return this->db_name;
}

void database_set_ip_address(database * this, char * ip_address)
{
	if(database_is_connected(this) == false)
		this->ip_address = ip_address;
}

char * database_get_ip_address(database * this)
{
	return this->ip_address;
}

void database_set_tcp_port(database * this, char * tcp_port)
{
	if(database_is_connected(this) == false)
		this->tcp_port = tcp_port;
}

char * database_get_tcp_port(database * this)
{
	return this->tcp_port;
}

void database_set_current_stock(database * this, const char * current_stock)
{
	this->current_stock = current_stock;
}

bool database_connect(database * this)
{
	if(database_is_connected(this) == false)
	{
		this->conn = PQconnectdb(c_string_get_char_array(this->connection));

		return database_is_connected(this);
	}
	else
	{
		return false;
	}
}

void database_disconnect(database * this)
{
	if(database_is_connected(this) == true)
		PQfinish(this->conn);
}

uint32_t database_get_item_number_in_stock(database * this)
{
	return 20;
}

uint32_t database_get_item_quantity(database * this, uint8_t ID)
{
	return 0;
}

char * database_get_item_name(database * this, uint8_t ID)
{
	return NULL;
}

char * database_get_item_shortcut_name(database * this, uint8_t ID)
{
	return NULL;
}

double database_get_item_tax(database * this, uint8_t ID)
{
	return 1.1;
}

double database_get_item_price(database * this, uint8_t ID)
{
	return 1.1;
}

bool database_set_item_quantity(database * this, uint8_t ID, uint32_t new_quantity)
{
	return false;
}	

bool database_is_connected(database * this)
{
 	if (PQstatus(this->conn) == CONNECTION_BAD) 
		return false;
	else
		return true;
}

void database_finalize(database * this)
{
	database_disconnect(this);
	free(this);
}


/***************************** modul order_list ***************************/
order_list * order_list_new()
{
	order_list * this = (order_list*) malloc(sizeof(order_list));

	this->order_service_ref = order_service_new();
	this->list = array_list_new();

	return this;
}

void order_list_increment_item_quantity_by_index(order_list * this, uint32_t index)
{
	order_item * item = order_list_get_order_item_by_index(this, index);

	if(item != NULL)
	  	order_item_increase_quantity(item);
}

uint8_t order_list_get_item_ID_by_index(order_list * this, uint32_t index)
{
	if(index < array_list_size(this->list))
	{
		order_item * item = array_list_get(this->list, index);
		return order_item_get_ID(item);
	}
	else
	{
		return 0;
	}
}

void order_list_decrement_item_quantity_by_index(order_list * this, uint32_t index)
{
	if(index < array_list_size(this->list))
		order_list_decrement_item_quantity_if_not_null(this, index);
}

static void order_list_decrement_item_quantity_if_not_null(order_list * this, uint32_t index)
{
	order_item * item = array_list_get(this->list, index);

	if(item != NULL)
	{
		if(order_list_remove_item_from_list_if_quantity_equals_zero(this, item, index) == false)
			order_item_decrease_quantity(item);	
	}
}

uint32_t order_list_find_order_by_ID(order_list * this, uint8_t ID)
{
	for(int i=0; i<array_list_size(this->list); i++)
	{
		order_item * item = array_list_get(this->list, i);

		if(order_item_get_ID(item) == ID)
		  return i;
	}

  	return 0xffffffff;
}

static bool order_list_remove_item_from_list_if_quantity_equals_zero(order_list * this, order_item * item, uint32_t index)
{	
	if(order_item_get_quantity(item) == 1)
	{
		array_list_remove_with_release(this->list, index, order_item_finalize);
		return true;
	}
	else
	{
		return false;
	}
}

void order_list_put_new_item_to_order_list(order_list * this, uint8_t ID, char * item_name, char * item_shortcut_name, double price, double tax)
{
	order_item * item = order_item_new(ID, item_name, item_shortcut_name, price, tax);
	
	array_list_add(this->list, item);
}

uint32_t order_list_size(order_list * this)
{
	return array_list_size(this->list);
}

double order_list_get_total_price_without_tax(order_list * this)
{
	double total_price = 0;

	for(int i = 0; i < array_list_size(this->list); i++)
	{
		order_item * item = order_list_get_order_item_by_index(this, i);
		total_price += order_item_get_total_price_without_tax(item);
	}

	return total_price;
}


double order_list_get_total_price_with_tax(order_list * this)
{
	double total_price = 0;

	for(int i = 0; i < array_list_size(this->list); i++)
	{
		order_item * item = order_list_get_order_item_by_index(this, i);
		total_price += order_item_get_total_price_with_tax(item);
	}

	return total_price;
}

void order_list_remove_by_index(order_list * this, uint32_t index)
{
	array_list_remove_with_release(this->list, index, order_item_finalize);
}

void order_list_clear(order_list * this)
{
	array_list_clear_with_release(this->list, order_item_finalize);
}

char * order_list_get_order_item_name_at_index(order_list * this, uint32_t index)
{
	order_item * item = order_list_get_order_item_by_index(this, index);

	if(item != NULL)
		return order_item_get_name(item);
	else
		return NULL;
}

uint32_t order_list_get_order_item_quantity_at_index(order_list * this, uint32_t index)
{
	order_item * item = order_list_get_order_item_by_index(this, index);

	if(item != NULL)
		return order_item_get_quantity(item);
	else
		return 0;
}

double order_list_get_order_item_price_withou_tax_at_index(order_list * this, uint32_t index)
{
	order_item * item = order_list_get_order_item_by_index(this, index);

	if(item != NULL)
		return order_item_get_total_price_without_tax(item);
	else
		return 0;
}

double order_list_get_order_item_price_with_tax_at_index(order_list * this, uint32_t index)
{
	order_item * item = order_list_get_order_item_by_index(this, index);

	if(item != NULL)
		return (order_item_get_total_price_with_tax(item));
	else
		return 0;

}

static order_item * order_list_get_order_item_by_index(order_list * this, uint8_t index)
{
	if(index < array_list_size(this->list))
		return array_list_get(this->list, index);
	else
		return NULL;
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
order_item * order_item_new(uint8_t ID, char * item_name, char * item_shortcut_name, double item_price, double tax)
{
	order_item * this = (order_item *) malloc(sizeof(order_item));

	this->ID = ID;
	this->item_name = item_name;
	this->item_shortcut_name = item_shortcut_name;
	this->item_price = item_price;
	this->quantity = 1;
	this->tax = tax;

	return this;
}

char * order_item_get_name(order_item * this)
{
	return this->item_name;
}

char * order_item_get_shortcut_name(order_item * this)
{
	return this->item_shortcut_name;
}

double order_item_get_price(order_item * this)
{
	return this->item_price;
}

uint32_t order_item_get_quantity(order_item * this)
{
	return this->quantity;
}

uint8_t order_item_get_ID(order_item * this)
{
	return this->ID;
}

double order_item_get_total_price_without_tax(order_item * this)
{
	return (this->item_price * this->quantity);
}

double order_item_get_total_price_with_tax(order_item * this)
{
	return (this->item_price * this->quantity * this->tax);
}

void order_item_increase_quantity(order_item * this)
{
	this->quantity ++;
}

void order_item_decrease_quantity(order_item * this)
{
	if(this->quantity > 0)
		this->quantity --;
}

void order_item_finalize(void * this)
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
	this->price_buffer = c_string_new();

	return this;
}

void view_base_build_container(view_base * this)
{
	this->stack_container = gtk_stack_new();

	gtk_widget_set_size_request(GTK_WIDGET(this->stack_container), 
			this->screen_geometry.width, 
			view_base_recount_y_geometry_by_ratio(this, this->window_base_geometry.height-125));
}

void view_base_redraw(view_base * this)
{
	gtk_widget_queue_draw(GTK_WIDGET(this->stack_container));
}

void view_base_set_current_window_geometry(view_base * this, geometry window_geometry)
{
	this->window_geometry.width = window_geometry.width;
	this->window_geometry.height = window_geometry.height;
}


alarm_buffer * view_base_get_alarm_baffer_ref(view_base * this)
{
	return this->controler_ref->alarm_buffer_ref;
}


controler * view_base_get_controler_reference(view_base * this)
{
	return this->controler_ref;
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

void view_base_screen_set_label_markup_text(GtkWidget * label, const char * string, ...)
{
	char label_text[128];
	va_list params;
	va_start(params, string);

	vsprintf(label_text, string ,params);
	gtk_label_set_markup(GTK_LABEL(label), label_text);

	va_end(params);
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

void view_initialize(view * this)
{
	view_base_show_order_screen(this->view_base_ref);
	gtk_widget_show_all(this->window);
	//view_hide_cursor(this);
}

static gboolean view_cyclic_interupt(gpointer param)
{
	view * this = (view*) param;

	view_base_redraw(this->view_base_ref);

	if(controler_database_is_connected(this->controler_ref) == false)
	{
		alarm_buffer_set_error(view_base_get_alarm_baffer_ref(this->view_base_ref), error_index_database_connection);
	}

	char number_buffer[16];
	sprintf(number_buffer, "%d Kč", (int) round(controler_get_order_total_price_with_tax(this->controler_ref)));

	c_string_set_string(this->view_base_ref->price_buffer, number_buffer);

	return TRUE;
}

static void view_hide_cursor(view * this)
{
	GdkCursor * cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_BLANK_CURSOR);
	GdkWindow * win = gtk_widget_get_window((this->window));
	gdk_window_set_cursor((win), cursor);
}

static void view_build_main_window(view * this)
{
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size(GTK_WINDOW(this->window), 
					this->view_base_ref->screen_geometry.width, 
					this->view_base_ref->screen_geometry.height);

	gtk_window_set_title(GTK_WINDOW(this->window), CONF_WINDOW_TITLE);
	gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_fullscreen (GTK_WINDOW(this->window));

	GdkPixbuf * program_icon = view_base_load_image(CONF_COMPANY_ICON_PATH);

	if(program_icon != NULL)
		gtk_window_set_icon(GTK_WINDOW(this->window), program_icon);

	this->container = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(this->window), this->container);
}

static GtkWidget * view_initialize_company_icon_widget(GdkPixbuf * icon, double window_width_ratio)
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

static bool view_load_company_icon(view * this)
{
	GdkPixbuf * icon = view_base_load_image(CONF_COMPANY_ICON_PATH);

	if(icon != NULL)
	{
		this->company_icon = view_initialize_company_icon_widget(icon, 
							this->view_base_ref->window_width_ratio);
		g_object_unref(icon);

		return true;
	}
	else
	{
		this->company_icon = NULL;

		return false;
	}
}

static void view_initialize_base_class(view * this)
{
	geometry window_base_geometry = {800, 600};

	this->view_base_ref = view_base_new(this->controler_ref, window_base_geometry);
	view_base_set_current_window_geometry(this->view_base_ref, 
						this->view_base_ref->screen_geometry);
}

static void view_build_screens(view * this)
{
	this->view_bill_viewer_screen_ref = view_bill_viewer_screen_new(this->view_base_ref);
	this->view_order_screen_ref = view_order_screen_new(this->view_base_ref);
	this->view_manual_input_screen_ref = view_manual_input_screen_new(this->view_base_ref);
	this->view_settings_screen_ref = view_settings_screen_new(this->view_base_ref);
	this->view_order_finish_screen_ref = view_order_finish_screen_new(this->view_base_ref);
}

static void view_build_alarm_widget(view * this)
{
	geometry widget_geometry;
	widget_geometry.width = this->view_base_ref->window_geometry.width;
	widget_geometry.height = view_base_recount_y_geometry_by_ratio(this->view_base_ref, 25);

	this->alarm_widget_ref = alarm_widget_new(view_base_get_alarm_baffer_ref(this->view_base_ref), widget_geometry);
	alarm_widget_set_font_size(this->alarm_widget_ref, 20);
	alarm_widget_set_font_family(this->alarm_widget_ref, "Arial");
	alarm_widget_set_left_padding(this->alarm_widget_ref, view_base_recount_x_geometry_by_ratio(this->view_base_ref, 50));
}

static void view_pack_screens(view * this)
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

static void view_pack_container(view * this)
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

static void view_signals(view * this)
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

static void view_finalize(view * this)
{
	view_bill_viewer_screen_finalize(this->view_bill_viewer_screen_ref);
	view_order_screen_finalize(this->view_order_screen_ref);
	view_manual_input_screen_finalize(this->view_manual_input_screen_ref);
	view_settings_screen_finalize(this->view_settings_screen_ref);
	view_order_finish_screen_finalize(this->view_order_finish_screen_ref);

	view_base_finalize(this->view_base_ref);

	gtk_main_quit();
}


static void view_window_exit_callback(GtkWidget * widget, gpointer param)
{
	view * this = (view*) param;
	view_finalize(this);
}

static void view_close_callback(GtkWidget * widget, GdkEventButton * event, gpointer * param)
{
	view * this = (view*) param;

	if(event->type == GDK_2BUTTON_PRESS)
	{
		view_finalize(this);
	}
	else
	{
		view_base_show_settings_screen(this->view_base_ref);	
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



controler * view_base_screen_get_controler_reference(view_base_screen * this)
{
	return view_base_get_controler_reference(this->view_base_ref);
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

	multi_lang_set_common_text_czech(lang_struct_cz);
	multi_lang_set_order_screen_text_czech(lang_struct_cz);
	multi_lang_set_manual_input_screen_text_czech(lang_struct_cz);
	multi_lang_set_order_finish_screen_text_czech(lang_struct_cz);
	multi_lang_set_settings_screen_text_czech(lang_struct_cz);
	multi_lang_set_bill_viewer_screen_text_czech(lang_struct_cz);
}

void multi_lang_set_common_text_czech(lang * this)
{
	this->currency_text = "Kč";
	this->default_sum_price_text = "0.0 Kč";
	this->btn_back_text = "Zpět";
}

void multi_lang_set_order_screen_text_czech(lang * this)
{
	this->btn_clear_order_text = "Nová platba";
	this->btn_increase_quantity_text = "+1";
	this->btn_decrease_quantity_text = "-1";
	this->btn_pay_text = "Zaplatit";
	this->btn_manual_input_text = "Zadat ručně";
	this->lbl_sum_text = "Celkem:";
	this->order_list_widget_goods_text = "Zboží";
	this->order_list_widget_quantity_text = "Množství";
	this->order_list_widget_price_without_tax_text = "Cena bez DPH";
	this->order_list_widget_price_with_tax_text = "Cena s DPH";
}

void multi_lang_set_manual_input_screen_text_czech(lang * this)
{
	this->btn_prev_text = "Předchozí";
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

void view_order_screen_build_list_widget(view_order_screen * this)
{
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	geometry window_base_geometry = view_base_ref->window_base_geometry;
	geometry widget_geometry;
	widget_geometry.width = view_base_recount_x_geometry_by_ratio(view_base_ref, window_base_geometry.width-100);
	widget_geometry.height = view_base_recount_y_geometry_by_ratio(view_base_ref, 300);

	this->list_widget = order_list_widget_new(widget_geometry);
	order_list_widget_set_source(this->list_widget, view_base_ref->controler_ref->order_list_ref);
	order_list_widget_set_font_size(this->list_widget, 30);
	order_list_widget_set_font_family(this->list_widget, "Arial");
	order_list_widget_set_visible_row_number(this->list_widget, 5);
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

	geometry widget_geometry;
	widget_geometry.width = view_base_recount_x_geometry_by_ratio(this->base_screen_ref->view_base_ref, 
									this->base_screen_ref->view_base_ref->window_base_geometry.width-100);
	widget_geometry.height = view_base_recount_y_geometry_by_ratio(this->base_screen_ref->view_base_ref, 35);
	
	double bg_color[3] = {0.91, 0.91, 0.91};

	this->order_sum_price = value_widget_new(widget_geometry);
	value_widget_set_background_color(this->order_sum_price, bg_color);
	value_widget_set_font_size(this->order_sum_price, 35);
	value_widget_set_left_padding(this->order_sum_price, 30);
	value_widget_set_right_padding(this->order_sum_price, 30);
	value_widget_set_font_family(this->order_sum_price, "Arial");
	value_widget_set_value(this->order_sum_price, this->base_screen_ref->view_base_ref->price_buffer);

}

void view_order_screen_language(view_order_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * btn_label;

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_clear_order));
	view_base_screen_set_label_markup_text(btn_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20,
			cz_lang->btn_clear_order_text);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_increase_quantity));
	view_base_screen_set_label_markup_text(btn_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20, 
			cz_lang->btn_increase_quantity_text);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_decrease_quantity));
	view_base_screen_set_label_markup_text(btn_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20,
			cz_lang->btn_decrease_quantity_text);

	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_pay));
	view_base_screen_set_label_markup_text(btn_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20, 
			cz_lang->btn_pay_text);
	
	btn_label = gtk_bin_get_child(GTK_BIN(this->btn_manual_input));
	view_base_screen_set_label_markup_text(btn_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20,
			cz_lang->btn_manual_input_text);

	value_widget_set_label(this->order_sum_price, cz_lang->lbl_sum_text);

	order_list_widget_add_column(this->list_widget, cz_lang->order_list_widget_goods_text);
	order_list_widget_add_column(this->list_widget, cz_lang->order_list_widget_quantity_text);
	order_list_widget_add_column(this->list_widget, cz_lang->order_list_widget_price_without_tax_text);
	order_list_widget_add_column(this->list_widget, cz_lang->order_list_widget_price_with_tax_text);
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
			this->order_sum_price->draw_area, 
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			labels_line_position);
	
	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), 
			order_list_widget_get_instance(this->list_widget),
			view_base_recount_x_geometry_by_ratio(view_base_ref, 50),
			view_base_recount_y_geometry_by_ratio(view_base_ref, 80));
}

gboolean view_order_screen_show_total_price_callback(GtkWidget * widget,  cairo_t * cr, gpointer param)
{
	view_order_screen * this = (view_order_screen *) param;
	controler * controler_ref = view_base_screen_get_controler_reference(this->base_screen_ref);

	gtk_widget_set_sensitive(GTK_WIDGET(this->btn_pay), controler_get_order_list_size(controler_ref) > 0);
	gtk_widget_set_sensitive(GTK_WIDGET(this->btn_increase_quantity), order_list_widget_is_selected(this->list_widget));
	gtk_widget_set_sensitive(GTK_WIDGET(this->btn_decrease_quantity), order_list_widget_is_selected(this->list_widget));

	return FALSE;
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

	g_signal_connect(G_OBJECT(this->base_screen_ref->container), 
			"draw", 
			G_CALLBACK(view_order_screen_show_total_price_callback), 
			this);

}

void view_order_screen_btn_manual_input_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_manual_input_screen((view_base*) param);
}


void view_order_screen_btn_increase_quantity_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_screen * this = (view_order_screen*) param;

	if(order_list_widget_is_selected(this->list_widget))
			controler_increase_item_quantity_by_index(view_base_screen_get_controler_reference(this->base_screen_ref),
														order_list_widget_get_selected_row(this->list_widget));

	view_base_redraw(this->base_screen_ref->view_base_ref);
}

void view_order_screen_btn_decrease_quantity_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_screen * this = (view_order_screen*) param;

	if(order_list_widget_is_selected(this->list_widget))
			controler_decrease_item_quantity_by_index(view_base_screen_get_controler_reference(this->base_screen_ref),
														order_list_widget_get_selected_row(this->list_widget));


	view_base_redraw(this->base_screen_ref->view_base_ref);
}

void view_order_screen_btn_pay_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_order_finish_screen((view_base*) param);
}

void view_order_screen_btn_clear_order_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_screen * this = (view_order_screen*) param;
	controler_clear_order_list(view_base_screen_get_controler_reference(this->base_screen_ref));	

	order_list_widget_initialize(this->list_widget);
	view_base_redraw(this->base_screen_ref->view_base_ref);
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
	this->page_index = 0;

	view_manual_input_screen_build_widgets(this);
	view_manual_input_screen_language(this);
	view_manual_input_screen_pack_widgets(this);
	view_manual_input_screen_fill(this);

	return this;
}

void view_manual_input_screen_fill(view_manual_input_screen * this)
{
	controler * controler_ref = view_base_screen_get_controler_reference(this->base_screen_ref);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			uint32_t ID = ((i*5)+(j+1)+(this->page_index*15));
			GtkWidget * button = this->button_matrix[i][j];

			if(ID <= controler_get_item_number_in_stock(controler_ref))
			{
				gtk_widget_set_sensitive(button, TRUE);
				GtkWidget * button_label = gtk_bin_get_child(GTK_BIN(button));
				char * item_name = controler_get_item_name_by_ID(controler_ref, ID);
				uint32_t item_quantity = controler_get_item_quantity_by_ID(controler_ref, ID);

				view_base_screen_set_label_markup_text(button_label, 
									"<span font_desc=\"%d\"><b>%s</b></span>\n<span font_desc=\"%d\"><b>(%d)</b></span>",
									20,
									item_name,
									10,
									item_quantity);
			}
			else
			{
				gtk_widget_set_sensitive(button, FALSE);
				gtk_button_set_label(GTK_BUTTON(this->button_matrix[i][j]), "");
			}
		}
	}
}

static void view_manual_input_screen_build_widgets(view_manual_input_screen * this)
{
	double btn_width = 150;
	double btn_height = 50;

	this->button_matrix = (GtkWidget ***) malloc(sizeof(GtkWidget **)*3);

	for(int i = 0; i < 3; i++)
	{
		this->button_matrix[i] = (GtkWidget **) malloc(sizeof(GtkWidget*)*5);

		for(int j = 0; j < 5; j++)
		{
			this->button_matrix[i][j] = view_base_screen_build_button(this->base_screen_ref, 150, 50);
			gtk_widget_set_sensitive(GTK_WIDGET(this->button_matrix[i][j]), FALSE);
			GtkWidget * button_label  = gtk_bin_get_child(GTK_BIN(this->button_matrix[i][j]));
			gtk_label_set_justify(GTK_LABEL(button_label), GTK_JUSTIFY_CENTER);
		}
	}

	this->btn_next = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
	this->btn_prev = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
	this->btn_back = view_base_screen_build_button(this->base_screen_ref, btn_width, btn_height);
}

static void view_manual_input_screen_language(view_manual_input_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * button_label;
	
	button_label = gtk_bin_get_child(GTK_BIN(this->btn_prev));
	view_base_screen_set_label_markup_text(button_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>",
			20,
			cz_lang->btn_prev_text);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_back));
	view_base_screen_set_label_markup_text(button_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>", 
			20, 
			cz_lang->btn_back_text);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_next));
	view_base_screen_set_label_markup_text(button_label, 
			"<span font_desc=\"%d\"><b>%s</b></span>",
			20,
			cz_lang->btn_next_text);
}

static void view_manual_input_screen_pack_widgets(view_manual_input_screen * this)
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

static void view_manual_input_screen_signals(view_manual_input_screen * this)
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

static void view_manual_input_screen_btn_prev_click_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen *) param;

	if(this->page_index > 0)
	{
		this->page_index --;
		gtk_widget_set_sensitive(this->btn_next, TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(this->btn_prev, FALSE);
	}

	view_manual_input_screen_fill(this);
}

static void view_manual_input_screen_add_item(view_manual_input_screen * this, uint8_t ID)
{
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	controler * controler_ref = view_base_screen_get_controler_reference(this->base_screen_ref);

	controler_update_order_list(controler_ref, ID);

	view_base_redraw(view_base_ref);
	view_base_show_order_screen(view_base_ref);
}

static void view_manual_input_screen_btn_back_click_callback(GtkWidget * widget, gpointer param)
{
	view_base_show_order_screen((view_base*) param);
}

static void view_manual_input_screen_btn_next_click_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen *) param;

	if(this->page_index < controler_get_item_number_in_stock(view_base_screen_get_controler_reference(this->base_screen_ref)))
	{
		this->page_index ++;	
		gtk_widget_set_sensitive(GTK_WIDGET(this->btn_prev), TRUE);
	}
	else
	{
		gtk_widget_set_sensitive(GTK_WIDGET(this->btn_next), FALSE);
	}

	view_manual_input_screen_fill(this);
}

static void view_manual_input_screen_button_metrix_0x0_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((0*5)+(0+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_0x1_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((0*5)+(1+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_0x2_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((0*5)+(2+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_0x3_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((0*5)+(3+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_0x4_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((0*5)+(4+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_1x0_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((1*5)+(0+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_1x1_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((1*5)+(1+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_1x2_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((1*5)+(2+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_1x3_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((1*5)+(3+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_1x4_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((1*5)+(4+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_2x0_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((2*5)+(0+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_2x1_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((2*5)+(1+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_2x2_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((2*5)+(2+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_2x3_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((2*5)+(3+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_button_metrix_2x4_clicked_callback(GtkWidget * widget, gpointer param)
{
	view_manual_input_screen * this = (view_manual_input_screen*) param;
	uint32_t ID = ((2*5)+(4+1)+(this->page_index*15));
	view_manual_input_screen_add_item(this, ID);
}

static void view_manual_input_screen_finalize(view_manual_input_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

/**************************** modul settings_parameter ****************************/

settings_parameter * settings_parameter_new(geometry widget_geometry, GtkWidget * entry, double pos_label, double pos_entry)
{
	settings_parameter * this = (settings_parameter *) malloc(sizeof(settings_parameter));

	settings_parameter_build_widgets(this, widget_geometry, entry);	
	settings_parameter_pack_widgets(this, pos_label, pos_entry);

	return this; 
}

static void settings_parameter_build_widgets(settings_parameter * this, geometry widget_geometry, GtkWidget * entry)
{
	this->container = gtk_fixed_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->container), widget_geometry.width, widget_geometry.height);

	this->label = gtk_label_new(NULL);
	gtk_widget_set_size_request(GTK_WIDGET(this->label), widget_geometry.width/4, widget_geometry.height);

	this->entry = entry;
}

static void settings_parameter_pack_widgets(settings_parameter * this, double pos_left, double pos_right)
{
	gtk_fixed_put(GTK_FIXED(this->container), this->label, pos_left, 0);
	gtk_fixed_put(GTK_FIXED(this->container), this->entry, pos_right, 0);
}

void settings_parameter_set_label(settings_parameter * this, const char * label_text)
{
	gtk_label_set_markup(GTK_LABEL(this->label), label_text);
}

GtkWidget * settings_parameter_get_container(settings_parameter * this)
{
	return this->container;
}

GtkWidget * settings_parameter_get_entry(settings_parameter * this)
{
	return this->entry;
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

	this->calculator_buffer = c_string_new_with_init("0 Kč");
	this->money_back_buffer = c_string_new_with_init("0 Kč");

	this->calculator_register = 0;

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_order_finish_screen_build_widgets(this);
	view_order_finish_screen_language(this);
	view_order_finish_screen_pack_widgets(this);

	return this;
}

void view_order_finish_screen_build_widgets(view_order_finish_screen * this)
{
	this->button_matrix = (GtkWidget ***) malloc(sizeof(GtkWidget**)*4);
	view_base * view_base_ref = this->base_screen_ref->view_base_ref;
	geometry window_base_geometry = view_base_ref->window_base_geometry;

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
	value_widget_geometry.width = view_base_recount_x_geometry_by_ratio(view_base_ref, 
									window_base_geometry.width-100);
	value_widget_geometry.height = view_base_recount_y_geometry_by_ratio(view_base_ref, 30);

	double bg_color_1[3] = {0.84, 0.84, 0.84};
	double bg_color_2[3] = {0.91, 0.91, 0.91};

	this->order_sum_price = view_order_build_value_widget(value_widget_geometry, bg_color_2, this->base_screen_ref->view_base_ref->price_buffer);
	this->customer_payed = view_order_build_value_widget(value_widget_geometry, bg_color_1, this->calculator_buffer);
	this->count_money_back = view_order_build_value_widget(value_widget_geometry, bg_color_2, this->money_back_buffer);
}

value_widget * view_order_build_value_widget(geometry widget_geometry, double bg_color[3], c_string * buffer)
{
	value_widget * value_widget_ref = value_widget_new(widget_geometry);
	value_widget_set_background_color(value_widget_ref, bg_color);
	value_widget_set_font_size(value_widget_ref, 30);
	value_widget_set_left_padding(value_widget_ref, 30);
	value_widget_set_right_padding(value_widget_ref, 30);
	value_widget_set_font_family(value_widget_ref, "Arial");
	value_widget_set_value(value_widget_ref, buffer);

	return value_widget_ref;
}

void view_order_finish_screen_language(view_order_finish_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);
	GtkWidget * button_label;
	
	button_label = gtk_bin_get_child(GTK_BIN(this->btn_print_bill));
	gtk_label_set_justify(GTK_LABEL(button_label), GTK_JUSTIFY_CENTER);
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>%s</b></span>", 20, cz_lang->btn_print_bill_text);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_back));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>%s</b></span>", 20, cz_lang->btn_back_text);

	button_label = gtk_bin_get_child(GTK_BIN(this->btn_finish));
	gtk_label_set_justify(GTK_LABEL(button_label), GTK_JUSTIFY_CENTER);
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>%s</b></span>", 20, cz_lang->btn_finish_text);

	value_widget_set_label(this->order_sum_price, cz_lang->lbl_order_sum_text);
	value_widget_set_label(this->customer_payed, cz_lang->lbl_customer_payed_text);
	value_widget_set_label(this->count_money_back, cz_lang->lbl_money_back_text);



	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][0]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>C</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][1]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>CE</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[0][2]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>0</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][0]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>1</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][1]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>4</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[1][2]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>7</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][0]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>2</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][1]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>5</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[2][2]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>8</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][0]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>3</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][1]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>6</b></span>", 20);

	button_label = gtk_bin_get_child(GTK_BIN(this->button_matrix[3][2]));
	view_base_screen_set_label_markup_text(button_label, "<span font_desc=\"%d\"><b>9</b></span>", 20);
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

void view_order_finish_screen_count_money_back(view_order_finish_screen * this)
{
	controler * controler_ref = view_base_screen_get_controler_reference(this->base_screen_ref);
	double order_price = controler_get_order_total_price_with_tax(controler_ref);

	if(this->calculator_register > order_price)
		view_order_finish_screen_convert_string_price(this->calculator_register - order_price , this->money_back_buffer);
	else
		view_order_finish_screen_convert_string_price(0, this->money_back_buffer);
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
			G_CALLBACK(view_order_finish_screen_button_matrix_1x2_click_callback),
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

void view_order_finish_screen_convert_string_price(uint32_t source_register, c_string * buffer)
{
	char string_price[16]; 
	sprintf(string_price, "%d Kč", source_register);
	c_string_set_string(buffer, string_price);
}

void view_order_finish_screen_append_digit_to_calculator_buffer(view_order_finish_screen * this, uint8_t digit)
{
	this->calculator_register = (this->calculator_register *10) + digit;
	
	view_order_finish_screen_convert_string_price(this->calculator_register, this->calculator_buffer);
	view_order_finish_screen_count_money_back(this);

	gtk_widget_queue_draw(GTK_WIDGET(this->customer_payed->draw_area));
	gtk_widget_queue_draw(GTK_WIDGET(this->count_money_back->draw_area));
}

void view_order_finish_screen_delete_digit_in_calculator_buffer(view_order_finish_screen * this)
{
	if(this->calculator_register > 0)
		this->calculator_register = (this->calculator_register / 10);

	view_order_finish_screen_convert_string_price(this->calculator_register, this->calculator_buffer);
	view_order_finish_screen_count_money_back(this);

	gtk_widget_queue_draw(GTK_WIDGET(this->customer_payed->draw_area));
	gtk_widget_queue_draw(GTK_WIDGET(this->count_money_back->draw_area));
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


	controler_clear_order_list(view_base_screen_get_controler_reference(this->base_screen_ref));	
}


void view_order_finish_screen_button_matrix_0x0_click_callback(GtkWidget * widget, gpointer param)
{
	c_string_set_string(((view_order_finish_screen*) param)->calculator_buffer, "0 Kč");
	((view_order_finish_screen *) param)->calculator_register = 0;

	view_order_finish_screen_count_money_back((view_order_finish_screen*) param);
}

void view_order_finish_screen_button_matrix_0x1_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_delete_digit_in_calculator_buffer((view_order_finish_screen *) param);
}

void view_order_finish_screen_button_matrix_0x2_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 0);
}

void view_order_finish_screen_button_matrix_1x0_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 1);
}

void view_order_finish_screen_button_matrix_1x1_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 4);
}

void view_order_finish_screen_button_matrix_1x2_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 7);
}

void view_order_finish_screen_button_matrix_2x0_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 2);
}

void view_order_finish_screen_button_matrix_2x1_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 5);
}

void view_order_finish_screen_button_matrix_2x2_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 8);
}

void view_order_finish_screen_button_matrix_3x0_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 3);
}

void view_order_finish_screen_button_matrix_3x1_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 6);
}

void view_order_finish_screen_button_matrix_3x2_click_callback(GtkWidget * widget, gpointer param)
{
	view_order_finish_screen_append_digit_to_calculator_buffer((view_order_finish_screen*) param, 9);
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

	alarm_widget_initialize_atributes(this);

	alarm_widget_build(this);

	return this;
}

void alarm_widget_initialize_atributes(alarm_widget * this)
{
	this->blink = false;

	this->font_size = 12;
	this->font_family = NULL;
	this->left_padding = 20;
}

void alarm_widget_set_font_size(alarm_widget * this, uint32_t font_size)
{
	this->font_size = font_size;
}

void alarm_widget_set_font_family(alarm_widget * this, const char * font_family)
{
	this->font_family = font_family;
}

void alarm_widget_set_left_padding(alarm_widget * this, double left_padding)
{
	this->left_padding = left_padding;
}

const char *  alarm_widget_get_next_error(alarm_widget * this)
{
	if(alarm_buffer_available_errors(this->alarm_buffer_ref) > 0)
	{
		alarm_report * report = alarm_buffer_get_next_error_report(this->alarm_buffer_ref);
		return alarm_report_get_description(report);
	}
	else
	{
		return NULL;
	}
}

const char * alarm_widget_get_next_warning(alarm_widget * this)
{
	if(alarm_buffer_available_warnings(this->alarm_buffer_ref) > 0)
	{
		alarm_report * report = alarm_buffer_get_next_warning_report(this->alarm_buffer_ref);
		return alarm_report_get_description(report);
	}
	else
	{
		return NULL;
	}
}

gboolean alarm_widget_draw_callback(GtkWidget * drawing_area, cairo_t * cr, gpointer param)
{
	alarm_widget * this = (alarm_widget*) param;
	const char * alarm_text = NULL;

	if(this->alarm_buffer_ref->error == true)
	{
		if(this->blink == true)
			cairo_set_source_rgb(cr, 1,0,0);
		else
			cairo_set_source_rgb(cr, 1,0.60,0.1);

		alarm_text = alarm_widget_get_next_error(this);

		this->blink = !this->blink;
	}
	else if(this->alarm_buffer_ref->warning == true)
	{
		cairo_set_source_rgb(cr, 1,0.60,0.1);
		alarm_text = alarm_widget_get_next_warning(this);
	}
	else
	{
		cairo_set_source_rgb(cr, 0,0.5,0);
	}

	cairo_rectangle(cr, 0,0, this->widget_geometry.width, this->widget_geometry.height);

	cairo_fill(cr);

	
	if((alarm_text != NULL) && (this->alarm_buffer_ref->error == true || this->alarm_buffer_ref->warning == true))
	{
		cairo_text_extents_t extents;

		cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
		cairo_set_font_size(cr, this->font_size);

		if(this->font_family != NULL)
			cairo_select_font_face(cr, this->font_family, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		
		cairo_text_extents(cr, alarm_text, &extents);

		cairo_move_to(cr, this->left_padding, (this->widget_geometry.height+extents.height)/2);
		cairo_show_text(cr, alarm_text);

		cairo_stroke(cr);
	}

	return TRUE;
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
				this);
}

void alarm_widget_reset_error_buffer_callback(GtkWidget * widget, GdkEventButton * event, gpointer param)
{
	alarm_widget * this = (alarm_widget*) param;
	alarm_buffer_reset(this->alarm_buffer_ref);
	gtk_widget_queue_draw(GTK_WIDGET(this->draw_area));
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

	value_widget_initialize_atributes(this);

	value_widget_build_widgets(this);

	value_widget_signals(this);

	return this;
}

void value_widget_build_widgets(value_widget * this)
{
	this->draw_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), 
					this->widget_geometry.width, 
					this->widget_geometry.height);
}

void value_widget_initialize_atributes(value_widget * this)
{
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

void value_widget_set_value(value_widget * this, c_string * value)
{
	this->value = value;
	gtk_widget_queue_draw(GTK_WIDGET(this->draw_area));
}

c_string * value_widget_get_value(value_widget * this)
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
		cairo_text_extents(cr, c_string_get_char_array(this->value), &extents);
		cairo_move_to(cr, this->widget_geometry.width - extents.width - this->right_padding, this->widget_geometry.height/2+extents.height/2);
		cairo_show_text(cr, c_string_get_char_array(this->value));
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
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), widget_geometry.width, widget_geometry.height-50);
	gtk_widget_add_events(GTK_WIDGET(this->draw_area), GDK_BUTTON_PRESS_MASK);

	this->header = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->header), widget_geometry.width, 50);

	this->scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(GTK_WIDGET(this->scroll), widget_geometry.width, widget_geometry.height-50);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(this->scroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_kinetic_scrolling(GTK_SCROLLED_WINDOW(this->scroll), TRUE);
	gtk_container_add(GTK_CONTAINER(this->scroll), this->draw_area);
	gtk_scrolled_window_set_propagate_natural_height (GTK_SCROLLED_WINDOW(this->scroll), TRUE);

	this->container = gtk_fixed_new();
	gtk_widget_set_size_request(GTK_WIDGET(this->container), widget_geometry.width, widget_geometry.height);
	gtk_fixed_put(GTK_FIXED(this->container), this->header, 0, 0);
	gtk_fixed_put(GTK_FIXED(this->container), this->scroll, 0, 50);

	this->header_columns = array_list_new();
	
	this->font_family = NULL;
	this->font_size = 12;

	this->source_order_list = FALSE;

	this->is_row_selected = false;;
	this->selected_row_index = 0;
	this->visible_row_number = 3;

	order_list_widget_signals(this);

	return this;
}

GtkWidget * order_list_widget_get_instance(order_list_widget * this)
{
	return this->container;
}

void order_list_widget_add_column(order_list_widget * this, const char * column_label)
{
	array_list_add(this->header_columns, (void*) column_label);
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

	g_signal_connect(G_OBJECT(this->header), 
				"draw",
				G_CALLBACK(order_list_widget_draw_header_column),
				this);

	g_signal_connect(G_OBJECT(this->draw_area),
				"button_press_event",
				G_CALLBACK(order_list_widget_click_callback),
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

gboolean order_list_widget_draw_header_column(GtkWidget * widget, cairo_t * cr, gpointer param)
{
	order_list_widget * this = (order_list_widget*) param;

	if(this->font_family != NULL)
		cairo_select_font_face(cr, this->font_family, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, this->font_size);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0,0, this->widget_geometry.width, 50);
	cairo_fill(cr);

	if(array_list_size(this->header_columns) > 0)
	{
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
		double column_width = this->widget_geometry.width/array_list_size(this->header_columns);
		double column_height = 50;

		for(int i = 0; i < array_list_size(this->header_columns); i++)
		{
			char * header_label = array_list_get(this->header_columns, i);
			cairo_text_extents_t extent;
			cairo_text_extents(cr, header_label, &extent);		

			cairo_move_to(cr, column_width*i + (column_width-extent.width)/2, ((extent.height+column_height))/2);
			cairo_show_text(cr, header_label);	
		}
	}

	cairo_stroke(cr);

	return FALSE;	
}

void order_list_widget_draw_content(order_list_widget * this, cairo_t * cr)
{
	int rows = order_list_size(this->source_order_list);	
	double column_width = this->widget_geometry.width/array_list_size(this->header_columns);
	double column_height = (this->widget_geometry.height-50)/(this->visible_row_number);

	for(int i = 0; i < rows; i++)
	{
		if((this->selected_row_index == i) && (this->is_row_selected == true))
		{
			cairo_set_source_rgb(cr, 1.0, 0.0, 1.0);	
		}
		else
		{
			if((i % 2) == 0)
				cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
			else
				cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);	
		}

		cairo_rectangle(cr, 0, column_height*(i), this->widget_geometry.width, column_height);
		cairo_fill(cr);

		cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

		char * order_name = order_list_get_order_item_name_at_index(this->source_order_list, i);
		uint32_t quantity = order_list_get_order_item_quantity_at_index(this->source_order_list, i);
		double price_without_tax = order_list_get_order_item_price_withou_tax_at_index(this->source_order_list, i);
		double price_with_tax = order_list_get_order_item_price_with_tax_at_index(this->source_order_list, i);
		char buffer[16];

		cairo_text_extents_t extent;

		cairo_text_extents(cr, order_name, &extent);		
		cairo_move_to(cr, (column_width-extent.width)/2, (column_height*(i)+(extent.height+column_height)/2));
		cairo_show_text(cr, order_name);	

		sprintf(buffer, "%d", quantity);
		cairo_text_extents(cr, buffer, &extent);		
		cairo_move_to(cr, column_width+(column_width-extent.width)/2, (column_height*(i)+(extent.height+column_height)/2));
		cairo_show_text(cr, buffer);


		sprintf(buffer, "%f", price_without_tax);
		cairo_text_extents(cr, buffer, &extent);		
		cairo_move_to(cr, column_width*2+(column_width-extent.width)/2, (column_height*(i)+(extent.height+column_height)/2));
		cairo_show_text(cr, buffer);

		sprintf(buffer, "%f", price_with_tax);
		cairo_text_extents(cr, buffer, &extent);		
		cairo_move_to(cr, column_width*3+(column_width-extent.width)/2, (column_height*(i)+(extent.height+column_height)/2));
		cairo_show_text(cr, buffer);

		cairo_stroke(cr);
	}
}

gboolean order_list_widget_draw_callback(GtkWidget * widget, cairo_t * cr, gpointer param)
{
	order_list_widget * this = (order_list_widget*) param;

	if((order_list_size(this->source_order_list) == 0) || (order_list_size(this->source_order_list) <= this->selected_row_index))
			this->is_row_selected = false;

	if(order_list_size(this->source_order_list) > this->visible_row_number)
	{
		double column_height = (this->widget_geometry.height-50)/(this->visible_row_number);
		gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), this->widget_geometry.width,50+(column_height*order_list_size(this->source_order_list) ));
	}

	if(this->font_family != NULL)
		cairo_select_font_face(cr, this->font_family, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, this->font_size);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0,0, this->widget_geometry.width, this->widget_geometry.height-50);
	cairo_fill(cr);

	order_list_widget_draw_content(this, cr);

	return FALSE;
}


void order_list_widget_set_font_size(order_list_widget * this, uint8_t font_size)
{
	this->font_size = font_size;
}

void order_list_widget_set_font_family(order_list_widget * this, const char * font_family)
{
	this->font_family = font_family;
}

void order_list_widget_initialize(order_list_widget * this)
{
	GtkAdjustment * adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(this->scroll));
	gtk_adjustment_set_value(GTK_ADJUSTMENT(adjustment), 0);
	gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(this->scroll), adjustment);

	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), this->widget_geometry.width, this->widget_geometry.height-50);
	gtk_widget_queue_draw(this->draw_area);

	this->is_row_selected = false;

}

gpointer order_list_widget_click_callback(GtkWidget * widget, GdkEventButton * event, gpointer param)
{
	order_list_widget * this = (order_list_widget *) param;
	double column_height = (this->widget_geometry.height-50)/(this->visible_row_number);
	int rows = order_list_size(this->source_order_list);	

	for(int i = 0; i < rows; i++)
	{
		if(event->y >= (column_height*i) && event->y <= (column_height*(i+1)))
		{
			if(this->is_row_selected == true) 
			{
			 	if(this->selected_row_index == i)
					this->is_row_selected = false;
				else
					this->is_row_selected = true;
			}
			else
			{
				this->is_row_selected = true;
			}

			this->selected_row_index = i;
		}
	}

	gtk_widget_queue_draw(GTK_WIDGET(widget));

	return FALSE;
}

gboolean order_list_widget_scroll_callback(GtkWidget * widget, GdkEventScroll * event, gpointer param)
{
	if(event->direction == GDK_SCROLL_UP)
		printf("nahoru\n");
	else if(event->direction == GDK_SCROLL_DOWN)
		printf("dolu\n");
	else
		printf("neco jineho\n");


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

/************************* unit testy pro modul user_management *******************/
void tc_user_management()
{

}


/*********************** unit testy pro modul eet_lib *****************************/
void tc_eet_lib()
{

}

/*********************** unit testy pro modul settings ****************************/
void tc_settings()
{

}

/*********************** unit testy pro modul printer *****************************/
void tc_printer()
{

}

/************************ unit testy pro modul system log *************************/
void tc_system_log()
{

}

/************************ unit testy pro modul database ***************************/
void tc_database()
{

}

/*********************** unit testy pro modul order_list *************************/
void tc_order_list()
{

}

/************************ unit testy pro modul order_service **********************/
void tc_order_service()
{

}

/************************ unit testy pro modul hand_scanner ************************/
void tc_hand_scanner()
{

}


/************************ unit testy pro modul order_item ****************************/
void tc_order_item()
{

}

/*********************** unit testy pro modul alarm_buffer ***************************/
void tc_alarm_buffer()
{

}

/******************************** unit testy pro modul controler ****************************/
void tc_controler()
{

}

/******************************** unit testy pro modul view_base ***************************/
void tc_view_base()
{

}

/****************************** unit testy pro modul multi_lang ****************************/
void tc_multi_lang()
{

}

/***************************** unit testy pro modul view_base_screen **********************/
void tc_view_base_screen()
{

}

/******************************* unit testy pro modul view_bill_browser *******************/
void tc_view_bill_browser_screen()
{

}

/******************************* unit testy pro modul order_screen ************************/
void tc_view_order_screen()
{

}

/****************************** unit testy pro modul manual_input *************************/
void tc_view_manual_input()
{

}

/****************************** unit testy pro modul view_settings_screen ******************/
void tc_view_settings_screen()
{

}

/***************************** unit testy pro modul finish_order_screen *******************/
void tc_view_finish_order_screen()
{

}

/***************************** unit testy pro modul alarm_widget *************************/
void tc_alarm_widget()
{

}

/***************************** unit testy pro modul value_widget ************************/
void tc_value_widget()
{

}

/**************************** unit testy pro modul view *********************************/
void tc_view()
{

}





void unit_test_runtime()
{
	//assert(false, "komentař: %d+%d=%d", 1,2,3);
	
	tc_user_management();
	tc_eet_lib();
	tc_settings();
	tc_printer();
	tc_system_log();
	tc_database();
	tc_order_list();
	tc_order_service();
	tc_hand_scanner();
	tc_order_item();
	tc_alarm_buffer();
	tc_controler();
	tc_view_base();
	tc_multi_lang();
	tc_view_base_screen();
	tc_view_bill_browser_screen();
	tc_view_order_screen();
	tc_view_manual_input();
	tc_view_settings_screen();
	tc_view_finish_order_screen();
	tc_alarm_widget();
	tc_value_widget();
	tc_view();
}


#endif










