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



/****************** definice struktur *********************************/



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

	uint32_t window_base_width;
	uint32_t window_base_height;

	uint32_t window_width;
	uint32_t window_height;

	uint32_t screen_width;
	uint32_t screen_height;

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

	const char * btn_clear_order_text;
	const char * btn_increase_quantity_text;
	const char * btn_decrease_quantity_text;
	const char * btn_pay_text;
	const char * btn_manual_input_text;
	const char * lbl_sum_text;
	const char * currency_text;
	const char * order_list_widget_goods_text;
	const char * order_list_widget_quantity_text;
	const char * order_list_widget_price_without_tax_text;
	const char * order_list_widget_price_with_tax_text;
};

struct _view_bill_viewer_screen_
{
	view_base_screen * base_screen_ref;
};

struct _view_order_screen_
{
	view_base_screen * base_screen_ref;
	
	GtkWidget * list;

	GtkWidget * btn_clear_order;
	GtkWidget * btn_increase_quantity;
	GtkWidget * btn_decrease_quantity;
	GtkWidget * btn_pay;
	GtkWidget * btn_manual_input;

	GtkWidget * lbl_sum_text;
	GtkWidget * lbl_sum_price;
};

struct _view_manual_input_screen_
{
	view_base_screen * base_screen_ref;

};

struct _view_settings_screen_
{
	view_base_screen * base_screen_ref;

};

struct _view_order_finish_screen_
{
	view_base_screen * base_screen_ref;

};

struct _alarm_widget_
{
	GtkWidget * draw_area;

	alarm_buffer * alarm_buffer_ref;

	uint32_t width;
	uint32_t height;

	bool blink;
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

view_base * view_base_new(controler * controler_ref, uint32_t window_base_width, uint32_t window_base_height);
void view_base_build_container(view_base * this);
void view_base_set_current_window_geometry(view_base * this, uint32_t window_width, uint32_t window_height);
void view_base_read_current_screen_geometry(view_base * this);
void view_base_show_order_screen(view_base * this);
void view_base_show_settings_screen(view_base * this);
void view_base_show_order_finish_screen(view_base * this);
void view_base_show_bill_viewer_screen(view_base * this);
void view_base_show_manual_input_screen(view_base * this);
void view_base_set_label_markup_text(GtkWidget * label, const char * string, int font_size);
void view_base_count_ratio(view_base * this);
double view_base_recount_horizontal_geometry_by_ratio(view_base * this, uint32_t base_position);
double view_base_recount_vertical_geometry_by_ratio(view_base * this, uint32_t base_position);
GdkPixbuf * view_base_load_image(char * image_address);
GdkPixbuf * view_base_scale_icon(GdkPixbuf * icon, enum _side_orientation_ axis, double new_size);
void view_base_finalize(view_base * this);

view_base_screen * view_base_screen_new(view_base * view_base_ref);
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
void view_order_screen_language(view_order_screen * this);
void view_order_screen_pack_widgets(view_order_screen * this);
void view_order_screen_signals(view_order_screen * this);
void view_order_screen_finalize(view_order_screen * this);

view_manual_input_screen * view_manual_input_screen_new(view_base * view_base_ref);
void view_manual_input_screen_build_widgets(view_manual_input_screen * this);
void view_manual_input_screen_language(view_manual_input_screen * this);
void view_manual_input_screen_pack_widgets(view_manual_input_screen * this);
void view_manual_input_screen_signals(view_manual_input_screen * this);
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
void view_order_finish_screen_finalize(view_order_finish_screen * this);

alarm_widget * alarm_widget_new(alarm_buffer * alarm_buffer_ref, uint32_t width, uint32_t height);
gboolean alarm_widget_draw_callback(GtkWidget * drawing_area, cairo_t * cr, gpointer param);
void alarm_widget_reset_error_buffer_callback(GtkWidget * widget, GdkEventButton * event, gpointer param);
void alarm_widget_build(alarm_widget * this);
void alarm_widget_signals(alarm_widget * this);
void alarm_widget_finalize(alarm_widget * this);


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

view_base * view_base_new(controler * controler_ref, uint32_t window_base_width, uint32_t window_base_height)
{
	view_base * this = (view_base*) malloc(sizeof(view_base));

	this->controler_ref = controler_ref;
	this->window_base_width = window_base_width;
	this->window_base_height = window_base_height;

	view_base_read_current_screen_geometry(this);

	view_base_build_container(this);

	this->multi_lang_ref = multi_lang_new();

	return this;
}

void view_base_build_container(view_base * this)
{
	this->stack_container = gtk_stack_new();

	gtk_widget_set_size_request(GTK_WIDGET(this->stack_container), 
			this->window_width, 
			view_base_recount_vertical_geometry_by_ratio(this, this->window_base_height-125));

}

void view_base_set_current_window_geometry(view_base * this, uint32_t window_width, uint32_t window_height)
{
	this->window_width = window_width;
	this->window_height = window_height;
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
	GdkRectangle geometry;

	GdkDisplay* display = gdk_display_get_default();
        GdkMonitor* monitor = gdk_display_get_monitor(display, 0);
        gdk_monitor_get_workarea(monitor, &geometry);

	this->screen_width = geometry.width;
	this->screen_height = geometry.height;

	view_base_count_ratio(this);
}

void view_base_set_label_markup_text(GtkWidget * label, const char * string, int font_size)
{
	char label_text[128];

	sprintf(label_text, "<span font_desc=\"%d\">%s</span>", font_size, string);
	gtk_label_set_markup(GTK_LABEL(label), label_text);
}

void view_base_count_ratio(view_base * this)
{
	this->window_width_ratio = ((double) this->screen_width) / ((double) this->window_base_width);
	this->window_height_ratio = ((double) this->screen_height) / ((double) this->window_base_height);
}

double view_base_recount_horizontal_geometry_by_ratio(view_base * this, uint32_t base_position)
{
	return (this->window_width_ratio * ((double) base_position));
}

double view_base_recount_vertical_geometry_by_ratio(view_base * this, uint32_t base_position)
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
			double scale = (((double) new_size)/((double)gdk_pixbuf_get_height(icon))) * ((double)gdk_pixbuf_get_width(icon));
			scaled_icon = gdk_pixbuf_scale_simple (icon, (int) scale, new_size, GDK_INTERP_HYPER);
		}
		else
		{
			double scale = (((double) new_size)/((double)gdk_pixbuf_get_width(icon))) * ((double)gdk_pixbuf_get_height(icon));
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
					this->view_base_ref->screen_width, 
					this->view_base_ref->screen_height);

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
	this->view_base_ref = view_base_new(this->controler_ref, 800, 600);
	view_base_set_current_window_geometry(this->view_base_ref, 
						this->view_base_ref->screen_width, 
						this->view_base_ref->screen_height);
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
	this->alarm_widget_ref = alarm_widget_new(this->view_base_ref->controler_ref->alarm_buffer_ref, 
					this->view_base_ref->window_width, 
					view_base_recount_vertical_geometry_by_ratio(this->view_base_ref, 25));

}

void view_pack_screens(view * this)
{
	/*
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
*/
	gtk_stack_add_named(GTK_STACK(this->view_base_ref->stack_container),
				this->view_order_screen_ref->base_screen_ref->container,
				"order_screen");

}

void view_pack_container(view * this)
{
	if(this->company_icon != NULL)
	{
		gtk_fixed_put(GTK_FIXED(this->container), 
				this->company_icon, 
				view_base_recount_horizontal_geometry_by_ratio(this->view_base_ref, (this->view_base_ref->window_base_width-200)/2+25),
				view_base_recount_vertical_geometry_by_ratio(this->view_base_ref, 30));	
	}

	gtk_fixed_put(GTK_FIXED(this->container), 
			this->alarm_widget_ref->draw_area,
			0,
			view_base_recount_vertical_geometry_by_ratio(this->view_base_ref, 100));

	gtk_fixed_put(GTK_FIXED(this->container),
			this->view_base_ref->stack_container,
			0,
			view_base_recount_vertical_geometry_by_ratio(this->view_base_ref, 125));
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
	this->order_list_widget_goods_text = "Zboží";
	this->order_list_widget_quantity_text = "Množství";
	this->order_list_widget_price_without_tax_text = "Cena bez DPH";
	this->order_list_widget_price_with_tax_text = "Cena s DPH";
}

void multi_lang_set_manual_input_screen_text_czech(lang * this)
{

}

void multi_lang_set_order_finish_screen_text_czech(lang * this)
{

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

void view_order_screen_build_widgets(view_order_screen * this)
{
	this->list = gtk_tree_view_new();

	this->btn_clear_order = gtk_button_new_with_label("");
	gtk_widget_set_size_request(GTK_WIDGET(this->btn_clear_order), 100,100);

	this->btn_increase_quantity = gtk_button_new();

	this->btn_decrease_quantity = gtk_button_new();
	this->btn_pay = gtk_button_new();
	this->btn_manual_input = gtk_button_new();

	this->lbl_sum_text = gtk_label_new(NULL);
	this->lbl_sum_price = gtk_label_new(NULL);
}

void view_order_screen_language(view_order_screen * this)
{
	lang * cz_lang = multi_lang_get_current_language(this->base_screen_ref->view_base_ref->multi_lang_ref);


	GtkWidget * btn_label = gtk_bin_get_child(GTK_BIN(this->btn_clear_order));

	view_base_set_label_markup_text(btn_label, cz_lang->btn_clear_order_text, 20);
}

void view_order_screen_pack_widgets(view_order_screen * this)
{
	gtk_fixed_put(GTK_FIXED(this->base_screen_ref->container), this->btn_clear_order, 100, 100);
}

void view_order_screen_signals(view_order_screen * this)
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

}

void view_manual_input_screen_language(view_manual_input_screen * this)
{

}

void view_manual_input_screen_pack_widgets(view_manual_input_screen * this)
{

}

void view_manual_input_screen_signals(view_manual_input_screen * this)
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

}


void view_order_finish_screen_language(view_order_finish_screen * this)
{

}

void view_order_finish_screen_pack_widgets(view_order_finish_screen * this)
{

}

void view_order_finish_screen_signals(view_order_finish_screen * this)
{

}

void view_order_finish_screen_finalize(view_order_finish_screen * this)
{
	view_base_screen_finalize(this->base_screen_ref);

	free(this);
}

/**************************** modul alarm_widget ****************************/

alarm_widget * alarm_widget_new(alarm_buffer * alarm_buffer_ref, uint32_t width, uint32_t height)
{
	alarm_widget * this = (alarm_widget *) malloc(sizeof(alarm_widget));

	this->alarm_buffer_ref = alarm_buffer_ref;
	this->width = width;
	this->height = height;
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

	cairo_rectangle(cr, 0,0, this->width, this->height);

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
	gtk_widget_set_size_request(GTK_WIDGET(this->draw_area), this->width, this->height);
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
		#if defined(_WIN32) || defined(_WIN64)
			HWND var = GetConsoleWindow();
			ShowWindow(var, SW_HIDE);
		#endif

		gtk_init(&argv, &argc);

		view_ref = view_new(controler_ref);
		view_signals(view_ref);
		view_initialize(view_ref);

		gtk_main();

		#if defined(_WIN32) || defined(_WIN64)
			ShowWindow(var, SW_SHOW);
		#endif
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








