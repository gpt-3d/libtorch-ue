#pragma once
#include "GenericPlatform/GenericPlatformCompilerPreSetup.h"
#include "Macros/AtumMacrosGuards.h"


// TORCH_INCLUDES_START
// #include <c10/util/Optional.h>
// #include <torch/nn/cloneable.h>
// #include <torch/nn/options/linear.h>
// #include <torch/nn/pimpl.h>
// #include <torch/types.h>
// TORCH_INCLUDES_END

TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END
#include "llama_config.h"
#include "rotary_embed.h"

#ifndef LLAMA_ATTENTION_H
#define LLAMA_ATTENTION_H

class LlamaAttentionImpl : public torch::nn::Module {
public:
    LlamaAttentionImpl(const LlamaConfig& config);

    std::tuple<torch::Tensor,  c10::optional<torch::Tensor>, c10::optional<std::tuple<torch::Tensor, torch::Tensor>>> forward(
        const torch::Tensor& hidden_states,
        const c10::optional<torch::Tensor>& attention_mask,
        const c10::optional<torch::Tensor>& position_ids,
        c10::optional<std::tuple<torch::Tensor, torch::Tensor>>& past_key_value,
        bool output_attentions = false,
        bool use_cache = false);

private:
    LlamaConfig config;
    int hidden_size;
    int num_heads;
    int head_dim;
    int num_key_value_groups;
    int max_position_embeddings;
    double rope_theta;
    bool is_causal;

    torch::nn::Linear q_proj, k_proj, v_proj, o_proj;

    // rotary embedding
    std::shared_ptr<LlamaRotaryEmbeddingImpl> rotary;

};

TORCH_MODULE(LlamaAttention);

#endif // LLAMA_ATTENTION_H
