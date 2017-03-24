/* ide-genesis-addin.h
 *
 * Copyright (C) 2015 Christian Hergert <chergert@redhat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IDE_GENESIS_ADDIN_H
#define IDE_GENESIS_ADDIN_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define IDE_TYPE_GENESIS_ADDIN (ide_genesis_addin_get_type())

G_DECLARE_INTERFACE (IdeGenesisAddin, ide_genesis_addin, IDE, GENESIS_ADDIN, GObject)

struct _IdeGenesisAddinInterface
{
  GTypeInterface parent_interface;

  gchar     *(*get_title)         (IdeGenesisAddin      *self);
  gchar     *(*get_icon_name)     (IdeGenesisAddin      *self);
  GtkWidget *(*get_widget)        (IdeGenesisAddin      *self);
  void       (*run_async)         (IdeGenesisAddin      *self,
                                   GCancellable         *cancellable,
                                   GAsyncReadyCallback   callback,
                                   gpointer              user_data);
  gboolean   (*run_finish)        (IdeGenesisAddin      *self,
                                   GAsyncResult         *result,
                                   GError              **error);
  gchar     *(*get_label)         (IdeGenesisAddin      *self);
  gchar     *(*get_next_label)    (IdeGenesisAddin      *self);
  gint       (*get_priority)      (IdeGenesisAddin      *self);
  GFile     *(*get_ready_project) (IdeGenesisAddin      *self);
};

gchar     *ide_genesis_addin_get_label         (IdeGenesisAddin      *self);
gchar     *ide_genesis_addin_get_next_label    (IdeGenesisAddin      *self);
gint       ide_genesis_addin_get_priority      (IdeGenesisAddin      *self);
gchar     *ide_genesis_addin_get_title         (IdeGenesisAddin      *self);
gchar     *ide_genesis_addin_get_icon_name     (IdeGenesisAddin      *self);
GtkWidget *ide_genesis_addin_get_widget        (IdeGenesisAddin      *self);
void       ide_genesis_addin_run_async         (IdeGenesisAddin      *self,
                                                GCancellable         *cancellable,
                                                GAsyncReadyCallback   callback,
                                                gpointer              user_data);
gboolean   ide_genesis_addin_run_finish        (IdeGenesisAddin      *self,
                                                GAsyncResult         *result,
                                                GError              **error);
GFile     *ide_genesis_addin_get_ready_project (IdeGenesisAddin      *self);

G_END_DECLS

#endif /* IDE_GENESIS_ADDIN_H */
