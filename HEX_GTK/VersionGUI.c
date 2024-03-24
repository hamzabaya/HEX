#include <gtk/gtk.h>
#include <stdlib.h>

#define GRID_SIZE 6

// Custom data structure to hold values
/**
 * \typedef Coord
 *
 * Structure representing coordinate information.
 */
typedef struct
{
    int ligne;    /**< The line or row. */
    char colonne; /**< The column. */
} Coord;

/**
 * \typedef Cell
 *
 * Structure representing a cell with a GtkWidget.
 */
typedef struct
{
    GtkWidget *event_box; /**< Pointer to a GtkWidget representing the cell. */
} Cell;

const gchar *text; /**< Pointer to constant character data. */

Cell cells[GRID_SIZE][GRID_SIZE]; /**< 2D array of Cell structures representing a grid of cells. */

gboolean cell_states[GRID_SIZE][GRID_SIZE] = {0}; /**< 2D array of boolean values representing cell states. */

gint playerRole = 0; /**< An integer representing the player's role. */

gint PLayerCells[GRID_SIZE][GRID_SIZE] = {0}; /**< 2D array of integers representing player-specific cell data. */


/**
 * \file
 * \brief This file contains functions for managing a grid-based game.
 */

/**
 * \brief Calculate coordinates based on character inputs.
 *
 * This function calculates coordinates based on character inputs for the grid.
 *
 * \param ligne The character representing the column ('1' to '6').
 * \param colonne The character representing the row ('A' to 'F').
 *
 * \return The Coord structure representing the calculated coordinates.
 */
Coord calcul_coords(char ligne, char colonne)
{
    Coord c;
    c.ligne = colonne - 'A';
    c.colonne = ligne - '1';
    return c;
}

/**
 * \brief Callback function to limit the text input to 2 characters.
 *
 * This function limits the input to a maximum of 2 characters.
 *
 * \param editable The editable widget.
 * \param user_data User-defined data.
 */
void on_entry_changed(GtkEditable *editable, gpointer user_data)
{
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(editable));

    // Check if the input length exceeds 2 characters
    if (g_utf8_strlen(text, -1) > 2)
    {
        // Truncate the input to 2 characters
        gchar *limited_text = g_utf8_substring(text, 0, 2);
        gtk_entry_set_text(GTK_ENTRY(editable), limited_text);
        g_free(limited_text);
    }
}

/**
 * \brief Callback function to handle Enter key press and display user input.
 *
 * This function handles the Enter key press, processes user input, and updates the display.
 *
 * \param entry The entry widget.
 * \param buffer The text buffer.
 */
void on_entry_activate(GtkEntry *entry, GtkTextBuffer *buffer)
{
    const gchar *user_input = gtk_entry_get_text(entry);

    // Clear the entry field
    // gtk_entry_set_text(entry, "");
    const gchar *input_text = gtk_entry_get_text(entry);

    // Split the input into two characters
    char colonne = g_utf8_get_char(input_text);
    input_text = g_utf8_next_char(input_text); // Move to the next character
    char ligne = g_utf8_get_char(input_text);

    if ((colonne >= 'A' && colonne <= 'F') && (ligne >= '1' && ligne <= '6'))
    {
        int x = calcul_coords(ligne, colonne).ligne;
        int y = calcul_coords(ligne, colonne).colonne;

        // Insert the user input into the text buffer on a new line
        if (PLayerCells[x][y] == 0)
        {
            GtkTextIter end_iter;
            gtk_text_buffer_get_end_iter(buffer, &end_iter);
            gtk_text_buffer_insert(buffer, &end_iter, user_input, -1);
            gtk_text_buffer_insert(buffer, &end_iter, "\n", -1);
        }

        change_cell_color(x, y);

        gtk_entry_set_text(entry, "");
    }
}

/**
 * \brief Change the background color of a cell.
 *
 * This function changes the background color of a cell based on the player's role.
 *
 * \param ligne The row of the cell.
 * \param colonne The column of the cell.
 */
void change_cell_color(int ligne, int colonne)
{
    if (PLayerCells[ligne][colonne] == 0)
    {
        if (playerRole % 2 == 0)
        {
            GdkRGBA color;
            gdk_rgba_parse(&color, "blue");
            gtk_widget_override_background_color(cells[ligne][colonne].event_box, GTK_STATE_FLAG_NORMAL, &color);
        }
        else
        {
            GdkRGBA color;
            gdk_rgba_parse(&color, "red");
            gtk_widget_override_background_color(cells[ligne][colonne].event_box, GTK_STATE_FLAG_NORMAL, &color);
        }
        PLayerCells[ligne][colonne] = -1;
        playerRole += 1;
    }
}


/**
 * \file
 * \brief This file contains functions for managing cell drawing and events.
 */

/**
 * \brief Callback function to draw cells and labels.
 *
 * This function draws cells and labels on a grid-based widget.
 *
 * \param widget The widget where drawing occurs.
 * \param cr The Cairo drawing context.
 * \param data User-defined data.
 *
 * \return FALSE to indicate that no further drawing is required.
 */
gboolean draw_cell_labels(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "col"));

    // Set the cell size to 80x80 pixels
    int cell_width = 80;
    int cell_height = 80;

    if (col < 55 & row < 71)
    {
        gchar label_text[1] = {data};
        PangoLayout *layout = gtk_widget_create_pango_layout(widget, label_text);

        // Set the font size to 20 pixels (20 * 1024 Pango units)
        PangoFontDescription *font_desc = pango_font_description_new();
        pango_font_description_set_absolute_size(font_desc, 20 * PANGO_SCALE);
        pango_layout_set_font_description(layout, font_desc);
        pango_font_description_free(font_desc);
        int layout_width, layout_height;
        pango_layout_get_pixel_size(layout, &layout_width, &layout_height);
        cairo_set_source_rgb(cr, 0, 0, 0); // Black text color
        cairo_move_to(cr, (cell_width - layout_width) / 2, (cell_height - layout_height) / 2);
        pango_cairo_show_layout(cr, layout);
        g_object_unref(layout);
    }

    // Check if the cell is in the first row and draw a red top border (20 pixels high)
    if (row == 64 && col < 55)
    {
        gdk_cairo_set_source_rgba(cr, &(GdkRGBA){1.0, 0.0, 0.0, 1.0}); // Red
        cairo_rectangle(cr, 0, 80 - 20, 80, 20);
        cairo_fill(cr);
    }

    // Check if the cell is in the first column and draw a blue left border (20 pixels wide)
    if (col == 48 && row < 71)
    {
        gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0.0, 0.0, 1.0, 1.0}); // Blue
        cairo_rectangle(cr, cell_width - 20, 0, 20, cell_height);
        cairo_fill(cr);
    }

    // Check if the cell is in the first row and draw a red top border (20 pixels high)
    if (row == 71 && col < 55 && col > 48)
    {
        gdk_cairo_set_source_rgba(cr, &(GdkRGBA){1.0, 0.0, 0.0, 1.0}); // Red
        cairo_rectangle(cr, 0, 0, cell_width, 20);
        cairo_fill(cr);
    }

    // Check if the cell is in the first column and draw a blue left border (20 pixels wide)
    if (col == 55 && row > 64)
    {
        gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0.0, 0.0, 1.0, 1.0}); // Blue
        cairo_rectangle(cr, 0, 0, 20, cell_height);
        cairo_fill(cr);
    }

    return FALSE;
}

/**
 * \brief Callback function for cell click event.
 *
 * This function handles cell click events and updates cell states.
 *
 * \param event_box The event box widget.
 * \param event The event details.
 * \param user_data User-defined data.
 */
void toggle_cell_state(GtkEventBox *event_box, GdkEventButton *event, gpointer user_data)
{
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(event_box), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(event_box), "col"));
    if (PLayerCells[row][col] == 0)
    {
        if (row - 65 >= 0 && row - 65 <= 5 && col - 49 >= 0 && col - 49 <= 5)
        {
            char x = (col - 49) + 'A';
            char y = (row - 65) + '1';
            printf("%c%c \n", x, y);
            change_cell_color(row - 65, col - 49);
        }
        gtk_widget_queue_draw(GTK_WIDGET(event_box));
    }
}

/**
 * \brief Callback function to draw cells.
 *
 * This function draws cells based on their states.
 *
 * \param widget The widget where drawing occurs.
 * \param cr The Cairo drawing context.
 * \param user_data User-defined data.
 *
 * \return FALSE to indicate that no further drawing is required.
 */
gboolean draw_cell(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "col"));

    if (cell_states[row][col] && PLayerCells[row][col] == 0)
    {
        cairo_rectangle(cr, 0, 0, gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
        cairo_fill(cr);
        PLayerCells[row][col] = -1;
    }

    // Draw the black border
    gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0.0, 0.0, 0.0, 1.0}); // Black
    cairo_rectangle(cr, 0, 0, gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
    cairo_stroke(cr);

    return FALSE;
}
/**
 * This function initializes the GTK+ library, sets up the graphical user interface,
 * and starts the GTK main loop.
 *
 * \param argc The number of command-line arguments.
 * \param argv An array of command-line arguments.
 *
 * \return 0 on successful execution.
 */
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Create a top-level window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hex Game Interface");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);

    // Create a red square container using a GtkBox
    GtkWidget *MainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Vertical box for red square
    gtk_container_add(GTK_CONTAINER(window), MainBox);

    // Create a left label
    GtkWidget *Label = gtk_label_new(NULL);

    // Set label's size to 20 pixels
    GtkCssProvider *cssLeftLabelProvider = gtk_css_provider_new();
    const gchar *markup = "<span foreground='blue' font='Bold 24'>Welcome to </span> <span foreground='red' font='Bold 24'>Hex Game</span>";
    gtk_label_set_markup(GTK_LABEL(Label), markup);

    // Create a horizontal box (GtkHBox)
    GtkWidget *UpperBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); // 10 is spacing between child elements
    GtkCssProvider *cssUpperBox = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
        GTK_CSS_PROVIDER(cssUpperBox),
        "#UpperBox { border-top:3px solid blue; border-bottom:3px solid red; margin: 30px; padding:20px}",
        -1,
        NULL);
    GtkStyleContext *HboxContext = gtk_widget_get_style_context(UpperBox);
    gtk_style_context_add_provider(HboxContext, GTK_STYLE_PROVIDER(cssUpperBox), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_box_pack_start(GTK_BOX(UpperBox), Label, TRUE, TRUE, 0); // Pack the label into the UpperBox
    gtk_widget_set_name(UpperBox, "UpperBox");

    // Add the upperbox to the mainbox
    gtk_box_pack_start(GTK_BOX(MainBox), UpperBox, FALSE, FALSE, 0);

    // Create a grid to hold the horizontal boxes
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE); // Disable equal column widths
    gtk_box_pack_start(GTK_BOX(MainBox), grid, FALSE, FALSE, 0);

    // Create a vertical box to hold the sections
    GtkWidget *LeftBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    // gtk_container_add(GTK_CONTAINER(window), LeftBox);
    gtk_grid_attach(GTK_GRID(grid), LeftBox, 0, 0, 1, 1);

    // Create the first section box
    GtkWidget *section1_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Create a CSS style context for the label
    GtkStyleContext *contextSection1 = gtk_widget_get_style_context(section1_box);

    // Apply a bottom margin top of 20 pixels using CSS
    gchar *cssMarginTop = "#section_margin { margin-top: 50px; }";
    GtkCssProvider *providerSection = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerSection, cssMarginTop, -1, NULL);
    gtk_style_context_add_provider(contextSection1, GTK_STYLE_PROVIDER(providerSection), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_set_name(section1_box, "section_margin");

    // Create label and entry box
    GtkWidget *user_value = gtk_label_new("Enter your move : ");

    // Create a CSS style context for the label
    GtkStyleContext *context = gtk_widget_get_style_context(user_value);

    // Apply a bottom margin of 20 pixels using CSS
    gchar *css = "#label { margin-bottom: 20px; }";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_set_name(user_value, "label");

    // Create a text buffer and a text view
    GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
    GtkWidget *text_view = gtk_text_view_new_with_buffer(buffer);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_width_chars(entry, 7);
    g_signal_connect(entry, "activate", G_CALLBACK(on_entry_activate), buffer);
    // Connect the "changed" signal to the callback function
    g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), NULL);

    // Add the label and entry to the first section box
    gtk_box_pack_start(GTK_BOX(section1_box), user_value, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(section1_box), entry, FALSE, FALSE, 0);

    // Create the second section box
    GtkWidget *section2_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

// Set the desired height for the text view (e.g., 200 pixels)
gtk_widget_set_size_request(text_view, -1, 200);

// Make the text view non-editable (disabled)
gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);

// Create a frame to contain the text view
GtkWidget *frame = gtk_frame_new(NULL);

// Set the frame's border width and border color
gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
GdkRGBA border_color;
gdk_rgba_parse(&border_color, "black");
gtk_widget_override_background_color(frame, GTK_STATE_FLAG_NORMAL, &border_color);

// Add the text view to the frame
gtk_container_add(GTK_CONTAINER(frame), text_view);

// Add the text view to the second section box
gtk_box_pack_start(GTK_BOX(section2_box), frame, FALSE, FALSE, 0);

// Add the section boxes to the vertical box
gtk_box_pack_start(GTK_BOX(LeftBox), section1_box, FALSE, FALSE, 0);
gtk_box_pack_start(GTK_BOX(LeftBox), section2_box, FALSE, FALSE, 0);

// Create the second horizontal box with a border and different width
GtkWidget *RightBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

// Adding the grid of buttons to the right box
GtkWidget *gridButtons = gtk_grid_new();
gtk_container_add(GTK_CONTAINER(RightBox), gridButtons);

Coord button_data[6][6];

// Create and add buttons to the grid
for (int row = 64; row < 72; row++)
{
    for (int col = 48; col < 56; col++)
    {
        if (row < 71 && col < 55)
        {
            button_data[row - 1][col - 1].ligne = col - 1;
            button_data[row - 1][col - 1].colonne = (row - 1) + '0';

            GtkWidget *event_box = gtk_event_box_new();

            gtk_widget_set_size_request(event_box, 80, 80); // Set cell size to 80x80 pixels
            gtk_grid_attach(GTK_GRID(gridButtons), event_box, col, row, 1, 1);

            g_signal_connect(event_box, "button-press-event", G_CALLBACK(toggle_cell_state), &button_data[row][col]);

            // Store the cell in the array
            if (row > 64 && row < 71 && col > 48 && col < 55)
            {
                cells[row - 65][col - 49].event_box = event_box;
            }

            // Set row and col data
            g_object_set_data(G_OBJECT(event_box), "row", GINT_TO_POINTER(row));
            g_object_set_data(G_OBJECT(event_box), "col", GINT_TO_POINTER(col));

            if (row > 64 && col > 48)
            {
                g_signal_connect(event_box, "draw", G_CALLBACK(draw_cell), NULL);
            }
            else if (!(row == 64 && col == 48))
            {
                if (row == 64)
                    g_signal_connect(event_box, "draw", G_CALLBACK(draw_cell_labels), (char)(row + col - 48));
                if (col == 48)
                    g_signal_connect(event_box, "draw", G_CALLBACK(draw_cell_labels), (row - 64) + '0');
            }
        }
        if (row == 71 || col == 55)
        {
            GtkWidget *event_box = gtk_event_box_new();

            gtk_widget_set_size_request(event_box, 80, 80); // Set cell size to 80x80 pixels
            gtk_grid_attach(GTK_GRID(gridButtons), event_box, col, row, 1, 1);

            g_signal_connect(event_box, "button-press-event", G_CALLBACK(toggle_cell_state), &button_data[row][col]);

            // Set row and col data
            g_object_set_data(G_OBJECT(event_box), "row", GINT_TO_POINTER(row));
            g_object_set_data(G_OBJECT(event_box), "col", GINT_TO_POINTER(col));

            if (!(row == 71 && col == 55))
            {
                if (row == 71)
                {
                    g_signal_connect(event_box, "draw", G_CALLBACK(draw_cell_labels), (char)(row + col - 48));
                }
                if (col == 55)
                {
                    g_signal_connect(event_box, "draw", G_CALLBACK(draw_cell_labels), (row - 64) + '0');
                }
            }
        }
    }
}

gtk_grid_attach(GTK_GRID(grid), RightBox, 1, 0, 2, 1);

// Set different column widths
GtkCssProvider *cssBoxes = gtk_css_provider_new();
gtk_css_provider_load_from_data(
    GTK_CSS_PROVIDER(cssBoxes),
    "#Boxes { border-top:3px solid blue; border-bottom:3px solid red; margin: 30px; padding:20px;}",
    -1, NULL

);
GtkStyleContext *LeftBoxContext = gtk_widget_get_style_context(LeftBox);
gtk_style_context_add_provider(LeftBoxContext, GTK_STYLE_PROVIDER(cssBoxes), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_widget_set_name(LeftBox, "Boxes");

GtkStyleContext *RightBoxContext = gtk_widget_get_style_context(RightBox);
gtk_style_context_add_provider(RightBoxContext, GTK_STYLE_PROVIDER(cssBoxes), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_widget_set_name(RightBox, "Boxes");

// Set different column widths using GtkAdjustment
GtkAdjustment *adjustment1 = gtk_adjustment_new(0.7, 0.0, 1.0, 0.05, 0.1, 0.0);
GtkAdjustment *adjustment2 = gtk_adjustment_new(0.3, 0.0, 1.0, 0.05, 0.1, 0.0);

gtk_widget_set_hexpand(RightBox, TRUE);
gtk_widget_set_hexpand(LeftBox, TRUE);

gtk_widget_set_halign(RightBox, GTK_ALIGN_FILL);
gtk_widget_set_halign(LeftBox, GTK_ALIGN_FILL);

// Show all widgets
gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}