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

struct _view_bill_viewer_screen_
{
	view_base_screen * base_screen_ref;
};

struct _view_order_screen_
{
	view_base_screen * base_screen_ref;

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
bool view_load_company_icon(view * this);
void view_pack_container(view * this);
void view_hide_cursor(view * this);
void view_initialize(view * this);
void view_build_main_window(view * this);
void view_build_screens(view * this);
void view_pack_screens(view * this);
void view_initialize_base_class(view * this);
void view_signals(view * this);
void view_finalize(GtkWidget * widget, void * param);

view_base * view_base_new(controler * controler_ref, uint32_t window_base_width, uint32_t window_base_height);
void view_base_set_current_window_geometry(view_base * this, uint32_t window_width, uint32_t window_height);
void view_base_read_current_screen_geometry(view_base * this);
void view_base_count_ratio(view_base * this);
double view_base_recount_horizontal_geometry_by_ratio(view_base * this, uint32_t base_position);
double view_base_recount_vertical_geometry_by_ratio(view_base * this, uint32_t base_position);
GdkPixbuf * view_base_load_image(char * image_address);
GdkPixbuf * view_base_scale_icon(GdkPixbuf * icon, uint8_t dimension, double new_size);
void view_base_finalize(view_base * this);

view_base_screen * view_base_screen_new(view_base * view_base_ref);
void view_base_screen_finalize(view_base_screen * this);

view_bill_viewer_screen * view_bill_viewer_screen_new(view_base * view_base_ref);
void view_bill_viewer_screen_build_widgets(view_bill_viewer_screen * this);
void view_bill_viewer_screen_pack_widgets(view_bill_viewer_screen * this);
void view_bill_viewer_screen_signals(view_bill_viewer_screen * this);
void view_bill_viewer_screen_finalize(view_bill_viewer_screen * this);

view_order_screen * view_order_screen_new(view_base * view_base_ref);
void view_order_screen_build_widgets(view_order_screen * this);
void view_order_screen_pack_widgets(view_order_screen * this);
void view_order_screen_signals(view_order_screen * this);
void view_order_screen_finalize(view_order_screen * this);

view_manual_input_screen * view_manual_input_screen_new(view_base * view_base_ref);
void view_manual_input_screen_build_widgets(view_manual_input_screen * this);
void view_manual_input_screen_pack_widgets(view_manual_input_screen * this);
void view_manual_input_screen_signals(view_manual_input_screen * this);
void view_manual_input_screen_finalize(view_manual_input_screen * this);

view_settings_screen * view_settings_screen_new(view_base * view_base_ref);
void view_settings_screen_build_widgets(view_settings_screen * this);
void view_settings_screen_pack_widgets(view_settings_screen * this);
void view_settings_screen_signals(view_settings_screen * this);
void view_settings_screen_finalize(view_settings_screen * this);

view_order_finish_screen * view_order_finish_screen_new(view_base * view_base_ref);
void view_order_finish_screen_build_widgets(view_order_finish_screen * this);
void view_order_finish_screen_pack_widgets(view_order_finish_screen * this);
void view_order_finish_screen_signals(view_order_finish_screen * this);
void view_order_finish_screen_finalize(view_order_finish_screen * this);

alarm_widget * alarm_widget_new(alarm_buffer * alarm_buffer_ref, uint32_t width, uint32_t height);
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

	return this;
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

	this->stack_container = gtk_stack_new();

	this->controler_ref = controler_ref;
	this->window_base_width = window_base_width;
	this->window_base_height = window_base_height;

	view_base_read_current_screen_geometry(this);

	return this;
}

void view_base_set_current_window_geometry(view_base * this, uint32_t window_width, uint32_t window_height)
{
	this->window_width = window_width;
	this->window_height = window_height;
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

void view_base_count_ratio(view_base * this)
{
	this->window_width_ratio = ((double)this->screen_width)/((double)this->window_base_width);
	this->window_height_ratio = ((double) this->screen_height)/((double)this->window_base_height);
}

double view_base_recount_horizontal_geometry_by_ratio(view_base * this, uint32_t base_position)
{
	return 0;
}

double view_base_recount_vertical_geometry_by_ratio(view_base * this, uint32_t base_position)
{
	return 0;
}

GdkPixbuf * view_base_load_image(char * image_address)
{
	GError * error = NULL;
	GdkPixbuf * image = gdk_pixbuf_new_from_file(image_address, &error);

	return image;
}

GdkPixbuf * view_base_scale_icon(GdkPixbuf * icon, uint8_t dimension, double new_size)
{
	GdkPixbuf* scaled_icon = NULL;

	if(icon != NULL)
	{
		if(dimension == 0)
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
	free(this);
}


/************************* modul view ***********************************/
view * view_new(controler * controler_ref)
{
	view * this = (view*) malloc(sizeof(view));

	this->controler_ref = controler_ref;

	view_initialize_base_class(this);
	view_build_main_window(this);

	view_build_screens(this);
	view_pack_screens(this);

	view_load_company_icon(this);

	view_pack_container(this);

	return this;
}


void view_hide_cursor(view * this)
{
	GdkCursor * cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_BLANK_CURSOR);
	GdkWindow * win = gtk_widget_get_window((this->window));
	gdk_window_set_cursor((win), cursor);
}

void view_initialize(view * this)
{
	gtk_widget_show_all(this->window);
	//view_hide_cursor(this);
}

void view_build_main_window(view * this)
{
	this->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size(GTK_WINDOW(this->window), this->view_base_ref->screen_width, this->view_base_ref->screen_height);
	gtk_window_set_title(GTK_WINDOW(this->window), CONF_WINDOW_TITLE);
	gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_fullscreen (GTK_WINDOW(this->window));
	gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);

	this->container = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(this->window), this->container);
}


bool view_load_company_icon(view * this)
{
	GdkPixbuf * icon = view_base_load_image(CONF_COMPANY_ICON_PATH);

	if(icon != NULL)
	{
		icon = view_base_scale_icon(icon, 1, 200*this->view_base_ref->window_height_ratio);
		//this->company_icon = gtk_image_new_from_pixbuf(icon);
		this->company_icon = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(this->company_icon), gtk_image_new_from_pixbuf(icon));
		gtk_widget_add_events(this->company_icon, GDK_2BUTTON_PRESS);
	
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
	view_base_set_current_window_geometry(this->view_base_ref, this->view_base_ref->screen_width, this->view_base_ref->screen_height);
}

void view_build_screens(view * this)
{
	this->view_bill_viewer_screen_ref = view_bill_viewer_screen_new(this->view_base_ref);
	this->view_order_screen_ref = view_order_screen_new(this->view_base_ref);
	this->view_manual_input_screen_ref = view_manual_input_screen_new(this->view_base_ref);
	this->view_settings_screen_ref = view_settings_screen_new(this->view_base_ref);
	this->view_order_finish_screen_ref = view_order_finish_screen_new(this->view_base_ref);
}

void view_pack_screens(view * this)
{

}

void view_pack_container(view * this)
{
	if(this->company_icon != NULL)
	{
		gtk_fixed_put(GTK_FIXED(this->container), 
				this->company_icon, 
				300,200);	
	}

}  

void view_signals(view * this)
{
	//g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(view_finalize), this);
	g_signal_connect(G_OBJECT(this->company_icon), "button_press_event", G_CALLBACK(view_finalize), this);

	view_bill_viewer_screen_signals(this->view_bill_viewer_screen_ref);
	view_order_screen_signals(this->view_order_screen_ref);
	view_manual_input_screen_signals(this->view_manual_input_screen_ref);
	view_settings_screen_signals(this->view_settings_screen_ref);
	view_order_finish_screen_signals(this->view_order_finish_screen_ref);
}

void view_finalize(GtkWidget * widget, void * param)
{
	view * this = (view*) param;

	view_bill_viewer_screen_finalize(this->view_bill_viewer_screen_ref);
	view_order_screen_finalize(this->view_order_screen_ref);
	view_manual_input_screen_finalize(this->view_manual_input_screen_ref);
	view_settings_screen_finalize(this->view_settings_screen_ref);
	view_order_finish_screen_finalize(this->view_order_finish_screen_ref);

	view_base_finalize(this->view_base_ref);

	gtk_main_quit();
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

/**************************** modul view_bill_viewer_screen ***********************/

view_bill_viewer_screen * view_bill_viewer_screen_new(view_base * view_base_ref)
{
	view_bill_viewer_screen * this = (view_bill_viewer_screen *) malloc(sizeof(view_bill_viewer_screen));

	this->base_screen_ref = view_base_screen_new(view_base_ref);

	view_bill_viewer_screen_build_widgets(this);
	view_bill_viewer_screen_pack_widgets(this);

	return this;
}

void view_bill_viewer_screen_build_widgets(view_bill_viewer_screen * this)
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
	view_order_screen_pack_widgets(this);

	return this;
}

void view_order_screen_build_widgets(view_order_screen * this)
{

}

void view_order_screen_pack_widgets(view_order_screen * this)
{

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
	view_manual_input_screen_pack_widgets(this);

	return this;
}

void view_manual_input_screen_build_widgets(view_manual_input_screen * this)
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
	view_settings_screen_pack_widgets(this);

	return this;
}

void view_settings_screen_build_widgets(view_settings_screen * this)
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
	view_order_finish_screen_pack_widgets(this);

	return this;
}

void view_order_finish_screen_build_widgets(view_order_finish_screen * this)
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

	alarm_widget_build(this);

	return this;
}

void alarm_widget_build(alarm_widget * this)
{

}

void alarm_widget_signals(alarm_widget * this)
{

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
	assert(false, "komentař: %d+%d=%d", 1,2,3);
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
