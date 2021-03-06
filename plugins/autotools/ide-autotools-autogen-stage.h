/* ide-autotools-autogen-stage.h
 *
 * Copyright (C) 2016 Christian Hergert <chergert@redhat.com>
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

#ifndef IDE_AUTOTOOLS_AUTOGEN_STAGE_H
#define IDE_AUTOTOOLS_AUTOGEN_STAGE_H

#include <ide.h>

G_BEGIN_DECLS

#define IDE_TYPE_AUTOTOOLS_AUTOGEN_STAGE (ide_autotools_autogen_stage_get_type())

G_DECLARE_FINAL_TYPE (IdeAutotoolsAutogenStage, ide_autotools_autogen_stage, IDE, AUTOTOOLS_AUTOGEN_STAGE, IdeBuildStage)

G_END_DECLS

#endif /* IDE_AUTOTOOLS_AUTOGEN_STAGE_H */
