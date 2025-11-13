/* 2025-10-12T21:56:04.595794 */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2025 Neuton.AI, Inc.
*
The source code and its binary form are being made available on the following terms:
Redistribution, use, and modification are permitted provided that the following
conditions are met:
*
1. Redistributions of source code and/or its binary form must retain the above copyright notice,
* this list of conditions (and the disclaimer) either in the body of the source code or in
* the documentation and/or other materials provided with the distribution of the binary form, as
applicable.
*
2. The name of the copyright holder may not be used to endorse or promote products derived from this
* source code or its binary form without specific prior written permission of Neuton.AI, Inc.
*
3. Disclaimer. THIS SOURCE CODE AND ITS BINARY FORM ARE PROVIDED BY THE COPYRIGHT HOLDER "AS IS".
* THE COPYRIGHT HOLDER HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
* OF THIRD PARTIES; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE OR ITS BINARY FORM, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------- */

static const neuton_weight_t MODEL_WEIGHTS[] =
{ 126, 126, 126, 126, 126, -1, -112, 78, 101, 97, 32, 1, -97, -33, -85, 56,
 126, 126, 92, -60, 126, -63, -95, -123, -21, -113, -119, 93, -64, 121,
 -128, -117, 124, 125, -52, 63, -126, -126, 126, 100, -126, -77 };

static const neuton_sources_num_t MODEL_LINKS[] =
{ 6, 9, 10, 11, 12, 16, 0, 16, 4, 5, 8, 10, 13, 16, 2, 0, 1, 9, 10, 16, 3,
 16, 2, 0, 1, 2, 7, 9, 12, 13, 14, 15, 16, 5, 16, 3, 5, 10, 16, 2, 7, 16 };

static const neuton_weights_num_t MODEL_INTERNAL_LINKS_BOUNDARIES[] =
{ 0, 7, 8, 15, 21, 23, 34, 35, 41 };

static const neuton_weights_num_t MODEL_EXTERNAL_LINKS_BOUNDARIES[] =
{ 6, 8, 14, 20, 22, 33, 35, 39, 42 };

static const neuton_coeff_t MODEL_ACTIVATION_COEFFS[] =
{ 0, 158, 0, 0, 160, 0, 158, 104, 154 };

static const neuton_u8_t MODEL_ACTIVATION_TYPE_MASK[] =
{ 0xad, 0x0 };

static const neuton_neurons_num_t MODEL_OUTPUT_NEURONS[] =
{ 1, 8, 4, 6 };
