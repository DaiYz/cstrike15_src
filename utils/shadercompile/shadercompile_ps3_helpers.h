//============ Copyright (c) Valve Corporation, All rights reserved. ============
//
// Functionality to handle collation of shader debugging metadata 
// (i.e. shader PDBs) sent from shadercompile workers to the master.
//
//===============================================================================

#pragma once

#ifndef SHADERCOMPILE_PS3_HELPERS_H
#define SHADERCOMPILE_PS3_HELPERS_H

#include "vmpi.h"

//-----------------------------------------------------------------------------
// The ID of the VMPI packet sent from workers to the master for each
// small PS3 shader debug metadata file generated by the Sony/Cg compiler.
//-----------------------------------------------------------------------------
#define PS3_SHADER_DEBUG_INFO_PACKETID 6
#define PS3_SHADER_COMPILE_LOG_PACKETID 11

//-----------------------------------------------------------------------------
// Structure of the packet corresponding to PS3_SHADER_DEBUG_INFO_PACKETID
//-----------------------------------------------------------------------------
struct PS3ShaderDebugInfoPacket_t
{
	char m_PacketID; // This should be PS3_SHADER_DEBUG_INFO_PACKETID
	int m_nFileNameLength;
	int m_nFileDataLength;
	// Followed by m_nFileNameLength + m_nFileDataLength bytes of data
};

//-----------------------------------------------------------------------------
// Handler for VMPI packet: PS3_SHADER_DEBUG_INFO_PACKETID.
// Called on the master when such a packet is received.
//-----------------------------------------------------------------------------
bool PS3ShaderDebugInfoDispatch( MessageBuffer *pBuf, int nSource, int nPacketID );

//-----------------------------------------------------------------------------
// Initializes the TOC and Pack files used to store the large amount
// of shader metadata generated by the worker machines.
// Called on the master.
//-----------------------------------------------------------------------------
void InitializePS3ShaderDebugPackFiles();

//-----------------------------------------------------------------------------
// Expand PS3 debug information that has been accumulated into giant pack
// files on the master's machine.
// These giant files expand into hundreds of thousands of tiny files
// required for shader debugging.
// Called on the master.
//-----------------------------------------------------------------------------
void ExpandPS3DebugInfo();

//-----------------------------------------------------------------------------
// Sends all files and non-empty directories to the VMPI master, one packet
// per file (see PS3_SHADER_DEBUG_INFO_PACKETID). Called by workers.
//-----------------------------------------------------------------------------
void SendSubDirectoryToMaster( const char *pStartingPath );

//-----------------------------------------------------------------------------
// Shader compile statistics log file
//-----------------------------------------------------------------------------
struct PS3ShaderCompileLogPacket_t
{
	char m_PacketID; // This should be PS3_SHADER_COMPILE_LOG_PACKETID
	int m_nPacketSize;
	// Followed by m_nPacketSize bytes of data
};

void PS3SendShaderCompileLogContentsToMaster();

bool PS3ShaderCompileLogDispatch( MessageBuffer *pBuf, int nSource, int nPacketID );

#endif // SHADERCOMPILE_PS3_HELPERS_H