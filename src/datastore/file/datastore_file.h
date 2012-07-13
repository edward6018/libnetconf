/**
 * \file datastore_file.h
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief NETCONF datastore handling function prototypes and structures for file datastore implementation.
 *
 * Copyright (C) 2012 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef DATASTORE_FILE_H_
#define DATASTORE_FILE_H_

#include "../datastore_internal.h"

struct ncds_ds_file {
	/**
	 * @brief Datastore implementation type
	 */
	NCDS_TYPE type;
	/**
	 * @brief Datastore ID: 0 - uninitiated datastore, positive value - valid ID
	 */
	ncds_id id;
	/**
	 * @brief Path to file containing YIN configuration data model
	 */
	char* model_path;
	/**
	 * @brief YIN configuration data model in the libxml2's document form.
	 */
	xmlDocPtr model;
	/**
	 * @brief Path to file containing configuration data, single file is
	 * used for all datastore types (running, startup, candidate).
	 */
	char* path;
	/**
	 * @brief File descriptor of opened file containing configuration data
	 */
	int fd;
	/**
	 * libxml2's document structure of the datastore
	 */
	xmlDocPtr xml;
	/**
	 * libxml2 Node pointers providing access to individual datastores
	 */
	xmlNodePtr candidate, running, startup;
};

/**
 * @brief Assign path of the datastore file into the datastore structure.
 *
 * Checks if the file exist and is accessible for reading and writing.
 * If the file does not exist it is created. File is opened and file
 * descriptor is stored in the structure
 *
 * @param[in] datastore Datastore structure to be configured.
 * @param[in] path File path to the file storing configuration datastores.
 * @return 0 on success
 * 	  -1 Invalid datastore
 *	  -2 Invalid path ((does not exist && can not be created) || insufficient rights)
 */
int ncds_file_set_path (struct ncds_ds* datastore, char* path);

/**
 * @brief Initialization of file datastore
 *
 * @param[in] file_ds File datastore structure
 * @return 0 on success, non-zero else
 */
int ncds_file_init (struct ncds_ds_file* file_ds);

#endif /* DATASTORE_FILE_H_ */
