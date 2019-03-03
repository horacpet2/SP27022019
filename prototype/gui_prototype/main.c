#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argv, char ** argc)
{
	gtk_init(&argv, &argc);

	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(GTK_WIDGET(window), 800, 600);

	GtkWidget * grid_container = gtk_grid_new();
	for(int i=0;i<6;i++)
	{
		gtk_grid_insert_row (GTK_GRID(grid_container), i);
	}	

	for(int i = 0;i<4;i++)
	{
		gtk_grid_insert_column (GTK_GRID(grid_container), i);
	}

	gtk_grid_set_row_homogeneous (GTK_GRID(grid_container), FALSE);
	gtk_grid_set_column_homogeneous (GTK_GRID(grid_container), FALSE);

	gtk_grid_set_row_spacing (GTK_GRID(grid_container), 3);
	gtk_grid_set_column_spacing (GTK_GRID(grid_container), 3);


	GtkWidget * vbox_line_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	

	GtkWidget * vbox_line_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);


	GtkWidget * vbox_line_3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);

	GtkWidget ** button_array = (GtkWidget **) malloc(sizeof(GtkWidget*)*3);

	gtk_container_add(GTK_CONTAINER(window), grid_container);

	for(int i=0;i<3; i++)
	{
		button_array[i] = gtk_button_new();
	}

	gtk_grid_attach(GTK_GRID(grid_container), button_array[0], 0, 0, 1,1);
	gtk_grid_attach(GTK_GRID(grid_container), button_array[1], 1, 0, 1,1);
	gtk_grid_attach(GTK_GRID(grid_container), button_array[2], 5, 1, 2,1);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
