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
#include <locale.h>
#include <pthread.h>
#include <gio/gio.h>
#include <gio/gnetworking.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif




/********************* definice konstant *******************************/

#define TEST FALSE

/******************** deklarace struktur *******************************/

struct _view_;
typedef struct _view_ View;

struct _view_base_;
typedef struct _view_base_ ViewBase;

struct _view_controler_;
typedef struct _view_controler_ ViewControler;

struct _view_base_screen_container_;
typedef struct _view_base_screen_container_ ViewBaseScreenContainer;

struct _view_base_screen_;
typedef struct _view_base_screen_ ViewBaseScreen;

struct _view_main_screen_;
typedef struct _view_main_screen_ ViewMainScreen;

struct _controler_;
typedef struct _controler_ Controler;

struct _geometry_;
typedef struct _geometry_ Geometry;





/******************** definice struktur *******************************/

struct _geometry_
{
	double x;
	double y;
};

struct _view_
{
	GtkWidget * window;
	ViewControler * viewControler;	
};

struct _view_controler_
{
	ViewBase * viewBase;
	Controler * controler;
	
	ViewMainScreen * viewMainScreen;
};

struct _view_base_window_container_
{
	GtkWidget * stackContainer;
};

struct _view_base_
{
	Geometry baseWidnowGeometry;
	Geometry windowGeometry;
	
	double verticalRatio;
	double horizontalRatio;
};

struct _view_base_screen_container_
{
	ViewBase * viewBase;
	
	GtkWidget * fixedContainer;	
};

struct _view_base_screen_
{
	ViewBaseScreenContainer * baseScreenContainer;		
};

struct _view_main_screen_
{
	ViewBaseScreen * baseScreen;	
};



struct _controler_
{

};

/***************** deklarace funkcí **********************************/

View * viewNew(Controler *);
void viewInitialize(View *);
static void viewBuildViewControler(View *);
static void viewSignals(View *);
static void viewBuildWindow(View *);
static void viewFinalize(View *);
static void viewExitCallback(GtkWidget *, gpointer);
static void viewWindowCloseCallback(GtkWidget *, gpointer);

ViewControler * viewControlerNew(Controler *);
void viewControlerSignals(ViewControler *);
GtkWidget * viewControlerGetContainer(ViewControler *);
void viewControlerFinalize(ViewControler *);




#if TEST == TRUE

void unitTestRuntime();
void assert(bool condition, char * comment, ...);

#endif


int main(int argv, char ** argc)
{
	setlocale(LC_ALL, "cs_CZ.utf8");

#if TEST == FALSE

	Controler * controler = NULL;

	if(controler != NULL)
	{
		gtk_init(&argv, &argc);

			View * view = viewNew(controler);
			viewInitialize(view);

		gtk_main();
	}
	else
	{
		fprintf(stderr, "Controler initialization error!\n");
	}
#else
	unitTestRuntime();
#endif

	return 0;
}



/********************* definice funkcí *******************************/

/****************** modul View ***************************************/

View * viewNew(Controler * controler)
{
	View * this = (View*) malloc(sizeof(View));

	viewBuildWindow(this);

	return this;
}

void viewInitialize(View * this)
{
	viewSignals(this);
	gtk_widget_show_all(this->window);
}

static void viewSignals(View * this)
{
	g_signal_connect(G_OBJECT(this->window), "destroy", G_CALLBACK(viewExitCallback), this);
}

static void viewBuildWindow(View * this)
{

}

static void viewFinalize(View * this)
{
	free(this);
}

static void viewExitCallback(GtkWidget * widget, gpointer param)
{
	viewFinalize((View*) param);
}

static void viewWindowCloseCallback(GtkWidget * widget, gpointer param)
{
	viewFinalize((View*) param);
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



void unitRestRuntime()
{
	//assert(false, "komentař: %d+%d=%d", 1,2,3);
}


#endif
