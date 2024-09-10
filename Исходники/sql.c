/*
 * If full_list is set, we list vertically, otherwise, we
 *  list on one line horizontally.
 * Return number of rows
 */
int list_result(JCR *jcr, B_DB *mdb, OUTPUT_FORMATTER *send, e_list_type type)
{
   SQL_FIELD *field;
   SQL_ROW row;
   int i, col_len, max_len = 0;
   int num_fields;
   char ewc[30];
   POOL_MEM key;
   POOL_MEM value;

   Dmsg0(800, "list_result starts\n");
   if (sql_num_rows(mdb) == 0) {
      send->decoration(_("No results to list.\n"));
      send->object_end("table");
      return sql_num_rows(mdb);
   }

   num_fields = sql_num_fields(mdb);
   switch (type) {
   case NF_LIST:
   case RAW_LIST:
      /*
       * No need to calculate things like column widths for
       * unformated or raw output.
       */
      break;
   case HORZ_LIST:
   case VERT_LIST:
      Dmsg1(800, "list_result starts looking at %d fields\n", num_fields);
      /*
       * Determine column display widths
       */
      sql_field_seek(mdb, 0);
      for (i = 0; i < num_fields; i++) {
         Dmsg1(800, "list_result processing field %d\n", i);
         field = sql_fetch_field(mdb);
         if (!field) {
            break;
         }
         col_len = cstrlen(field->name);
         if (type == VERT_LIST) {
            if (col_len > max_len) {
               max_len = col_len;
            }
         } else {
            if (sql_field_is_numeric(mdb, field->type) && (int)field->max_length > 0) { /* fixup for commas */
               field->max_length += (field->max_length - 1) / 3;
            }
            if (col_len < (int)field->max_length) {
               col_len = field->max_length;
            }
            if (col_len < 4 && !sql_field_is_not_null(mdb, field->flags)) {
               col_len = 4;                 /* 4 = length of the word "NULL" */
            }
            field->max_length = col_len;    /* reset column info */
         }
      }
      break;
   }

   Dmsg0(800, "list_result finished first loop\n");

   switch (type) {
   case NF_LIST:
   case RAW_LIST:
      Dmsg1(800, "list_result starts second loop looking at %d fields\n", num_fields);
      while ((row = sql_fetch_row(mdb)) != NULL) {
         send->object_start(row[0]);
         sql_field_seek(mdb, 0);
         for (i = 0; i < num_fields; i++) {
            field = sql_fetch_field(mdb);
            if (!field) {
               break;
            }
            if (row[i] == NULL) {
               value.bsprintf(" %s", "NULL");
            } else {
               value.bsprintf(" %s", row[i]);
            }
            send->object_key_value(field->name, value.c_str(), "%s");
         }
         if (type != RAW_LIST) {
            send->decoration("\n");
         }
         send->object_end(row[0]);
      }
      break;
   case HORZ_LIST:
      Dmsg1(800, "list_result starts second loop looking at %d fields\n", num_fields);
      list_dashes(mdb, send);
      send->decoration("|");
      sql_field_seek(mdb, 0);
      for (i = 0; i < num_fields; i++) {
         Dmsg1(800, "list_result looking at field %d\n", i);
         field = sql_fetch_field(mdb);
         if (!field) {
            break;
         }
         max_len = max_length(field->max_length);
         send->decoration(" %-*s |", max_len, field->name);
      }
      send->decoration("\n");
      list_dashes(mdb, send);

      Dmsg1(800, "list_result starts third loop looking at %d fields\n", num_fields);
      while ((row = sql_fetch_row(mdb)) != NULL) {
         send->object_start(row[0]);
         sql_field_seek(mdb, 0);
         send->decoration("|");
         for (i = 0; i < num_fields; i++) {
            field = sql_fetch_field(mdb);
            if (!field) {
               break;
            }
            max_len = max_length(field->max_length);
            if (row[i] == NULL) {
               value.bsprintf(" %-*s |", max_len, "NULL");
            } else if (sql_field_is_numeric(mdb, field->type) && !jcr->gui && is_an_integer(row[i])) {
               value.bsprintf(" %*s |", max_len, add_commas(row[i], ewc));
            } else {
               value.bsprintf(" %-*s |", max_len, row[i]);
            }
            if (i == num_fields-1) {
               value.strcat("\n");
            }
            /* use value format string to send preformated value */
            send->object_key_value(field->name, row[i], value.c_str());
         }
         send->object_end(row[0]);
      }
      list_dashes(mdb, send);
      break;
   case VERT_LIST:
      Dmsg1(800, "list_result starts vertical list at %d fields\n", num_fields);
      while ((row = sql_fetch_row(mdb)) != NULL) {
         send->object_start(row[0]);
         sql_field_seek(mdb, 0);
         for (i = 0; i < num_fields; i++) {
            field = sql_fetch_field(mdb);
            if (!field) {
               break;
            }
            if (row[i] == NULL) {
               key.bsprintf(" %*s: ", max_len, field->name);
               value.bsprintf("%s\n", "NULL");
            } else if (sql_field_is_numeric(mdb, field->type) && !jcr->gui && is_an_integer(row[i])) {
               key.bsprintf(" %*s: ", max_len, field->name);
               value.bsprintf("%s\n", add_commas(row[i], ewc));
            } else {
               key.bsprintf(" %*s: ", max_len, field->name);
               value.bsprintf("%s\n", row[i]);
            }
            /* use value format string to send preformated value */
            send->object_key_value(field->name, key.c_str(), row[i], value.c_str());
         }
         send->decoration("\n");
         send->object_end(row[0]);
      }
      break;
   }
   return sql_num_rows(mdb);
}